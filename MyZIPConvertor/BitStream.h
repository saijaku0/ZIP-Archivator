#pragma once

#include <fstream>
#include <iostream>
#include "BitReader.h"

class BitWriter {
    unsigned char buffer_ = 0; 
    int bit_count_ = 0;        
    std::ofstream& output_file_; 

public:
    BitWriter(std::ofstream& output) : output_file_(output) {}

    BitWriter(const BitWriter&) = delete;
    BitWriter& operator=(const BitWriter&) = delete;

    void write_bit(bool bit);

    void flush();
};