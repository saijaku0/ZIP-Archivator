#include "ArchiveCore.h"
#include <iostream>
#include <string>
#include <limits> 

int main() {
    std::cout << "=== Huffman Archiver ===\n";
    std::cout << "Select action:\n";
    std::cout << "1. Compress file\n";
    std::cout << "2. Decompress file\n";
    std::cout << "Your choice (1 or 2): ";

    int choice;
    while (!(std::cin >> choice)) {
        std::cout << "Error! Please enter number 1 or 2: ";
        std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer
    }

    std::string input_file;
    std::string output_file;

    std::cout << "\nEnter input filename (e.g. test.txt): ";
    std::cin >> input_file;

    std::cout << "Enter output filename (e.g. result.huf): ";
    std::cin >> output_file;

    ArchiverCore core;

    std::cout << "\n--- Starting process ---\n";

    try {
        if (choice == 1) {
            core.compress(input_file, output_file);
        }
        else if (choice == 2) {
            core.decompress(input_file, output_file);
        }
        else {
            std::cerr << "❌ Error: Invalid operation choice.\n";
        }
    }
    catch (const std::exception& e) {
        std::cerr << "\n🛑 ERROR: " << e.what() << std::endl;
        std::cerr << "Check if file '" << input_file << "' exists and is in the project directory.\n";
    }
    catch (...) {
        std::cerr << "\n🛑 Unknown error occurred.\n";
    }

    std::cout << "\nPress Enter to exit...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    std::cin.get(); 

    return 0;
}