#include <bitset>
#include "message.h"

#include <Streaming.h>

Message::Message() {}


bool Message::check_parity() {
    return parity_bit() == calculate_parity_bit();
}

uint8_t Message::header_byte() {
    return data_[0];
}


uint8_t Message::command_byte() {
    return data_[1];
}


uint8_t Message::parity_bit() {
    return  header_byte() >> 7;
}


uint8_t Message::calculate_parity_bit() {
    size_t sum = 0;
    for (size_t i=0; i<num_bytes_; i++) {
        uint8_t byte = data_[i];
        if (i==0) {
            byte &= 0b11111110;
        }
        sum += std::bitset<sizeof(uint8_t)>(byte).count();
    }
    return sum % 2;
}


uint8_t Message::calculate_8bit_checksum() {
    size_t sum = 0;
    for (size_t i=0; i<num_bytes_; i++) {
        sum += data_[i];
    }
    return uint8_t(sum);
}


size_t &Message::num_bytes() {
    return num_bytes_;
}


uint8_t *Message::data_ptr() {
    return data_.data();
}


void Message::print_data() {
    for (size_t i=0; i<num_bytes_; i++) {
        Serial << data_[i] << endl;
    }
}



