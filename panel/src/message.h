#ifndef MESSAGE_H
#define MESSAGE_H
#include <array>
#include "constants.h"
#include "pattern.h"

class Message {

    public:

        Message();

        size_t num_bytes();
        void set_num_bytes(size_t num_bytes);

        uint8_t header_byte();
        void set_header_byte(uint8_t header_byte);

        uint8_t command_byte();
        void set_command_byte(uint8_t command_byte);

        uint8_t parity_bit();
        void set_parity_bit();

        bool check_parity();
        bool check_length();
        bool check_protocol(uint8_t protocol=CMD_PROTOCOL);

        size_t payload_size();
        uint8_t &payload_at(size_t n);

        void from_pattern(Pattern &pat, uint8_t protocol=CMD_PROTOCOL);
        Pattern to_pattern(bool &err);

        void to_comms_check(uint8_t protocol=CMD_PROTOCOL);

        uint8_t calculate_parity_bit();
        uint8_t calculate_8bit_checksum();

        void print_data();

        friend void panel_spi_read(Message &msg); 

    protected:

        std::array<uint8_t, MESSAGE_MAXIMUM_SIZE> data_ {0};
        size_t  num_bytes_ = 0;

        void from_pattern_gray_2(Pattern &pat, uint8_t protocol);
        void from_pattern_gray_16(Pattern &pat, uint8_t protocol);

};

#endif
