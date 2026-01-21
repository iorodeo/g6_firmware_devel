#include <hardware/spi.h>
#include <hardware/gpio.h>
#include "messenger.h"
#include "panel_spi_custom.h"

#include <Streaming.h>


Messenger::Messenger() {
}

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

    bool parity_ok = msg.check_parity();


    count_ += 1;
    if (count_ % 1000 == 0) {
        Serial << "count: " << count_; 
        Serial << ", parity_bit  = " << msg.parity_bit();
        Serial << ", parity_calc = " << msg.calculate_parity_bit() << endl;
        //msg.print_data();
    }

    // Read spi messages (blocking)
    //msg.num_bytes = custom_spi_read_blocking(spi0, 0, msg.data, SPI_BUFF_SIZE, SPI_CS_PIN);
    if (msg.num_bytes() != 200) {
        Serial << "short!"<< endl; 
    }

}









