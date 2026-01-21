#ifndef MESSAGE_H
#define MESSAGE_H
#include <array>
#include "constants.h"

class Message {

    public:

        Message();

        bool check_parity();

        uint8_t header_byte();
        uint8_t command_byte();
        uint8_t parity_bit();

        uint8_t calculate_parity_bit();
        uint8_t calculate_8bit_checksum();

        size_t &num_bytes();
        uint8_t *data_ptr();

        void print_data();
        
    private:
        std::array<uint8_t, SPI_BUFF_SIZE> data_ {0};
        size_t  num_bytes_ = 0;

};



#endif
