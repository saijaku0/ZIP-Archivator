#pragma once

#include "Huffman.h" 
#include "BitStream.h" 
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

const int HUFF_MAGIC = 0x55464648; 

class ArchiverCore {
private:
    void write_header(std::ofstream& output_file, const CodeTable& table);
    std::shared_ptr<HuffmanNode> read_header(std::ifstream& input_file);
    void compress_data(std::ifstream& input, std::ofstream& output, const CodeTable& codes);
    void decompress_data(std::ifstream& input, std::ofstream& output, const std::shared_ptr<HuffmanNode>& root);
public:
    Frequencies count_frequencies(const std::string& filename);
    void compress(const std::string& input_file, const std::string& output_file);
    void decompress(const std::string& input_file, const std::string& output_file);
};