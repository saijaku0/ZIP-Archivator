#include "BitStream.h"

void BitWriter::write_bit(bool bit) {
    buffer_ <<= 1;

    if (bit) {
        buffer_ |= 1;
    }

    bit_count_++;

    if (bit_count_ == 8) {
        output_file_.write(reinterpret_cast<const char*>(&buffer_), sizeof(buffer_));

        buffer_ = 0;
        bit_count_ = 0;
    }
}

void BitWriter::flush() {
    if (bit_count_ > 0) {
        buffer_ <<= (8 - bit_count_);

        output_file_.write(reinterpret_cast<const char*>(&buffer_), sizeof(buffer_));
    }
    buffer_ = 0;
    bit_count_ = 0;
}