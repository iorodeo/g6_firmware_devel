#include <hardware/spi.h>
#include <hardware/gpio.h>
#include "messenger.h"
#include "panel_spi_custom.h"
#include <Streaming.h>


Messenger::Messenger() {}

void Messenger::initialize() { 

    // Setup SPI
    spi_init(spi0, SPI_SPEED);
    gpio_init(SPI_SCK_PIN);
    gpio_init(SPI_MOSI_PIN);
    gpio_init(SPI_MISO_PIN);
    gpio_init(SPI_CS_PIN);
    gpio_set_function(SPI_MOSI_PIN, GPIO_FUNC_SPI);
    gpio_set_function(SPI_SCK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(SPI_MISO_PIN, GPIO_FUNC_SPI);
    gpio_set_function(SPI_CS_PIN, GPIO_FUNC_SPI);
    spi_set_slave(spi0, true);
    spi_set_format(spi0, 8, SPI_CPOL_1, SPI_CPHA_1, SPI_MSB_FIRST);
}

void Messenger::update() { 

    static Message msg;
    panel_spi_read(msg);

    msg_count_ += 1;
    if (msg_count_ % 1000 == 0) {
        //msg.to_comms_check();

        Pattern pat;
        pat.set_gray_level(GrayLevel::Gray_2);
        pat.set_stretch(255);

        pat.matrix() << 
            1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0; 

        Message msg; 
        msg.from_pattern(pat);

        Serial << endl;

        for (size_t i=0; i<msg.payload_size(); i++) {
            Serial << i << ", " << msg.payload_at(i) << endl;
        }
        Serial << endl;

        bool err = false;
        Pattern pat2 = msg.to_pattern(err);
        Serial << "err: " << err << endl;
        for (size_t i=0; i<PANEL_SIZE; i++) {
            for (size_t j=0; j<PANEL_SIZE; j++) {
                Serial << pat2.at(i,j) << " ";
            }
            Serial << endl;
        }
        Serial << endl;


        bool length_ok = msg.check_length();
        bool parity_ok = msg.check_parity();
        Serial << "gray_level: ";
        if (pat.gray_level() == GrayLevel::Gray_2) {
            Serial << 2;
        }
        else {
            Serial << 16;
        }
        Serial << endl;
        Serial << "msg_count:  " << msg_count_ << endl;; 
        Serial << "length_ok:  " << length_ok << endl;
        Serial << "parity_ok:  " << parity_ok << endl;
        Serial << endl;
        //msg.print_data();
    }

}









