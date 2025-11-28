#include "ArchiveCore.h"

void ArchiverCore::compress(const std::string& input_file, const std::string& output_file) {
    Frequencies frequencies = count_frequencies(input_file);

    Huffman huffman;
    huffman.build_tree(frequencies);
    CodeTable codes = huffman.generate_codes();

    std::ifstream input(input_file, std::ios::binary);
    std::ofstream output(output_file, std::ios::binary);

    if (!input.is_open() || !output.is_open()) {
        throw std::runtime_error("Could open the file.");
    }

    write_header(output, codes);
    compress_data(input, output, codes);

    std::cout << "✅ Файл успешно сжат: " << output_file << std::endl;
}

void ArchiverCore::decompress(const std::string& input_file, const std::string& output_file) {
    std::ifstream input(input_file, std::ios::binary);
    std::ofstream output(output_file, std::ios::binary);

    if (!input.is_open() || !output.is_open()) {
        throw std::runtime_error("Could open the file.");
    }

    std::shared_ptr<HuffmanNode> root = read_header(input);

    if (!root) {
        throw std::runtime_error("Error: could decompress tree");
    }

    decompress_data(input, output, root);

    std::cout << "✅ Succsses: " << output_file << std::endl;
}

Frequencies ArchiverCore::count_frequencies(const std::string& filename) {
    std::ifstream input_file(filename, std::ios::binary);

    if (!input_file) {
        std::cerr << "ERROR: Could open file." << filename << std::endl;
        return Frequencies{};
    }

    Frequencies freq_map{};

    char byte_char;

    while (input_file.get(byte_char)) {
        unsigned char byte_index = static_cast<unsigned char>(byte_char);
        freq_map[byte_index]++;
    }

    return freq_map;
}

//-----------------
//  Private func
//-----------------

void ArchiverCore::write_header(std::ofstream& output_file, const CodeTable& table) {
    output_file.write(reinterpret_cast<const char*>(&HUFF_MAGIC), sizeof(HUFF_MAGIC));

    int unique_byte_count = static_cast<int>(table.size());
    output_file.write(reinterpret_cast<const char*>(&unique_byte_count), sizeof(unique_byte_count));

    for (const auto& pair : table) {
        unsigned char byte = pair.first;
        const auto& code = pair.second;

        output_file.write(reinterpret_cast<const char*>(&byte), sizeof(byte));

        unsigned char code_length = static_cast<unsigned char>(code.size());
        output_file.write(reinterpret_cast<const char*>(&code_length), sizeof(code_length));

        BitWriter writer(output_file);
        for (bool bit : code) {
            writer.write_bit(bit);
        }
        writer.flush();
    }
}

std::shared_ptr<HuffmanNode> ArchiverCore::read_header(std::ifstream& input_file) {
    int magic = 0;
    input_file.read(reinterpret_cast<char*>(&magic), sizeof(magic));
    if (magic != HUFF_MAGIC) {
        throw std::runtime_error("Incorect format (Magic Number).");
    }

    int unique_byte_count = 0;
    input_file.read(reinterpret_cast<char*>(&unique_byte_count), sizeof(unique_byte_count));

    if (unique_byte_count == 0) return nullptr;

    Frequencies frequencies{};
    BitReader reader(input_file);

    for (int i = 0; i < unique_byte_count; ++i) {
        unsigned char byte;
        unsigned char code_length;

        input_file.read(reinterpret_cast<char*>(&byte), sizeof(byte));
        input_file.read(reinterpret_cast<char*>(&code_length), sizeof(code_length));

        frequencies[byte] = 1;
        bool bit;
        for (int j = 0; j < code_length; ++j) {
            if (!reader.read_bit(bit)) {
                throw std::runtime_error("Error read bit of code");
            }
        }
    }

    Huffman huffman_builder;
    return huffman_builder.build_tree(frequencies);
}

void ArchiverCore::decompress_data(std::ifstream& input, std::ofstream& output, const std::shared_ptr<HuffmanNode>& root) {
    if (!root) return;

    BitReader reader(input);
    std::shared_ptr<HuffmanNode> current_node = root;
    bool bit;

    while (reader.read_bit(bit)) {
        if (bit == false) {
            current_node = current_node->left;
        }
        else {
            current_node = current_node->right;
        }

        if (current_node->is_leaf()) {
            output.write(reinterpret_cast<const char*>(&current_node->byte_value), sizeof(unsigned char));

            current_node = root;
        }
    }
}

void ArchiverCore::compress_data(std::ifstream& input, std::ofstream& output, const CodeTable& codes) {
    input.clear();
    input.seekg(0, std::ios::beg);

    BitWriter writer(output);
    char byte_char;

    while (input.get(byte_char)) {
        unsigned char byte = static_cast<unsigned char>(byte_char);

        auto it = codes.find(byte);
        if (it != codes.end()) {
            const std::vector<bool>& code = it->second;

            for (bool bit : code) {
                writer.write_bit(bit);
            }
        }
    }

    writer.flush();
}