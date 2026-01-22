#include <bitset>
#include <algorithm>
#include "message.h"

#include <Streaming.h>

Message::Message() {}


size_t Message::num_bytes() {
    return num_bytes_;
}


void Message::set_num_bytes(size_t num_bytes) {
    num_bytes_ = std::min(MESSAGE_MAXIMUM_SIZE, num_bytes);
    num_bytes_ = std::max(MESSAGE_MINIMUM_SIZE, num_bytes_);
}


uint8_t Message::header_byte() {
    return data_.at(0);
}


void Message::set_header_byte(uint8_t header_byte) {
    data_.at(0) = header_byte & 0b01111111;
}


uint8_t Message::command_byte() {
    return data_.at(1);
}

void Message::set_command_byte(uint8_t command_byte) {
    data_.at(1) = command_byte;
}


uint8_t Message::parity_bit() {
    return bitRead(header_byte(), 7);
}


void Message::set_parity_bit() {
    uint8_t parity = calculate_parity_bit();
    bitWrite(data_.at(0), 7, parity); 
}


bool Message::check_parity() {
    return parity_bit() == calculate_parity_bit();
}


bool Message::check_length() {
    bool ok = num_bytes_ >= MESSAGE_MINIMUM_SIZE; 
    uint8_t cmd = command_byte();
    if (PAYLOAD_SIZE_UMAP.find(cmd) != PAYLOAD_SIZE_UMAP.end()) {
        size_t payload_size = PAYLOAD_SIZE_UMAP.at(cmd);
        if (num_bytes_ != (payload_size + HEADER_SIZE)) {
            ok = false;
        }
    }
    return ok;
}


bool Message::check_protocol(uint8_t protocol) {
    return header_byte() == protocol;
}


void Message::from_pattern(Pattern &pat, uint8_t protocol) {
    switch (pat.gray_level()) {
        case GrayLevel::Gray_2:
            from_pattern_gray_2(pat, protocol);
            break;
        case GrayLevel::Gray_16:
            from_pattern_gray_16(pat, protocol);
            break;
        default:
            // TODO: set some kind of error pattern.
            break;
    }
}

Pattern Message::to_pattern(bool &err) {
    Pattern pat;
    return pat;
}

void Message::to_comms_check(uint8_t protocol) {
    uint8_t cmd = CMD_ID_COMMS_CHECK;
    size_t payload_size = PAYLOAD_SIZE_UMAP.at(cmd);

    set_num_bytes(HEADER_SIZE + payload_size);
    set_header_byte(protocol);
    set_command_byte(cmd);

    // Set payload to 0, 1, 2, .... 200
    for (size_t i=0; i<payload_size; i++) {
        payload_at(i) = uint8_t(i);
    }

    //Set the parity bit from the message data
    set_parity_bit();
}


size_t Message::payload_size() {
    return num_bytes_ - HEADER_SIZE;
}


uint8_t &Message::payload_at(size_t n) {
    size_t i = std::min(n + HEADER_SIZE, num_bytes_-1);
    return data_.at(i);
}


uint8_t Message::calculate_parity_bit() {
    size_t sum = 0;
    for (size_t i=0; i<num_bytes_; i++) {
        uint8_t byte = data_.at(i);
        if (i==0) {
            // Mask parity bit
            byte &= 0b01111111; 
        }
        sum += std::bitset<sizeof(uint8_t)>(byte).count();
    }
    return sum % 2;
}


uint8_t Message::calculate_8bit_checksum() {
    size_t sum = 0;
    for (size_t i=0; i<num_bytes_; i++) {
       sum += data_.at(i);
    }
    return uint8_t(sum);
}


void Message::print_data() {
    for (size_t i=0; i<num_bytes_; i++) {
        Serial << data_.at(i) << endl;
    }
}


// Protected methods
// -------------------------------------------------------------

void Message::from_pattern_gray_2(Pattern &pat, uint8_t protocol) {
    if (pat.gray_level() != GrayLevel::Gray_2) {
        return;
    }

    uint8_t cmd_id = CMD_ID_DISPLAY_GRAY_2;
    size_t payload_size = PAYLOAD_SIZE_UMAP.at(cmd_id);
    size_t total_size = HEADER_SIZE + payload_size;

    // Set message header
    set_num_bytes(total_size);
    set_header_byte(protocol);
    set_command_byte(cmd_id);

    // Pack pattern pixel data
    size_t pixel_num = 0;
    for (size_t i=0; i<PANEL_SIZE; i++) {
        for (size_t j=0; j<PANEL_SIZE; j++) {
            size_t byte_num = pixel_num/8;
            // TODO: change to MSB 
            size_t bit_pos = pixel_num - 8*byte_num;
            uint8_t pixel_value = pat.at(i,j) & 0b00000001;
            bitWrite(payload_at(byte_num), bit_pos, pixel_value);
            pixel_num++;
        }
    }

    // Add stretch value
    data_.at(total_size-1) = pat.stretch();
    set_parity_bit();
}

void Message::from_pattern_gray_16(Pattern &pat, uint8_t protocol) {
    if (pat.gray_level() != GrayLevel::Gray_16) {
        return;
    }

    uint8_t cmd_id = CMD_ID_DISPLAY_GRAY_16;
    size_t payload_size = PAYLOAD_SIZE_UMAP.at(cmd_id);
    size_t total_size = HEADER_SIZE + payload_size;

    // Set message header
    set_num_bytes(total_size);
    set_header_byte(protocol);
    set_command_byte(cmd_id);

    // Pack pattern pixel data
    size_t pixel_num = 0;
    for (size_t i=0; i<PANEL_SIZE; i++) {
        for (size_t j=0; j<PANEL_SIZE; j++) {
            uint8_t bit_shift  = (pixel_num%2 == 0) ? 0 : 4;
            uint8_t pixel_value = (pat.at(i,j) >> bit_shift) & 0b00001111;


            pixel_num++;
        }
    }

    // Add stretch value
    data_.at(total_size-1) = pat.stretch();
    set_parity_bit();
}

