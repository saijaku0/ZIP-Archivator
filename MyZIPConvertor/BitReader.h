#pragma once

#include <fstream>
#include <iostream>

class BitReader {
private:
    unsigned char buffer_ = 0; 
    int bit_count_ = 0;        
    std::ifstream& input_file_; 

public:
    BitReader(std::ifstream& input) : input_file_(input) {}

    bool read_bit(bool& result) {
        if (bit_count_ == 0) {
            char byte_char;
            if (!input_file_.get(byte_char)) {
                return false; 
            }
            buffer_ = static_cast<unsigned char>(byte_char);
            bit_count_ = 8;
        }

        result = (buffer_ >> (bit_count_ - 1)) & 1;

        bit_count_--; 
        return true;
    }
};