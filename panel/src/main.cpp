#include <Streaming.h>
#include "constants.h"
#include "messenger.h"

//#include <ArduinoEigen.h>
//#include <bitset>
//#include <pico.h>
//#include <hardware/spi.h>


// Core 0
// -----------------------------------------------------------

Messenger messenger;

void setup() {
    Serial.begin(115200);
    messenger.initialize();
}

void loop() {
    messenger.update();
}


// Core 1
// -----------------------------------------------------------
bool core1_separate_stack = true;

void setup1() {
}

void loop1() {
    delay(100);
}







//constexpr uint32_t NUM_BYTES = 200; 
//const uint8_t      SPI_SCK_PIN = 34;
//const uint8_t      SPI_MOSI_PIN = 32;
//const uint8_t      SPI_MISO_PIN = 35;
//const uint8_t      SPI_CS_PIN = 33;
//const uint32_t     SPI_SPEED = 30000000;
//const uint32_t     NUM_SKIP = 500;
//
//
//// SPI blocking read - modified to fix synchronization issue. 
//int __not_in_flash_func(wbd_spi_read_blocking)(
//        spi_inst_t *spi, 
//        uint8_t    repeated_tx_data, 
//        uint8_t    *dst, 
//        size_t     len, 
//        uint8_t    cs_pin
//    ) 
//{
//    invalid_params_if(HARDWARE_SPI, 0 > (int)len);
//    const size_t fifo_depth = 8;
//    size_t rx_remaining = len, tx_remaining = len;
//    int num_rx = 0;
//
//    // Wait until spi is readable
//    while(!spi_is_readable(spi)) {}; 
//
//    while (rx_remaining || tx_remaining) {
//        if (tx_remaining && spi_is_writable(spi) && rx_remaining < tx_remaining + fifo_depth) 
//        {
//            spi_get_hw(spi)->dr = (uint32_t) repeated_tx_data;
//            --tx_remaining;
//        }
//        if (rx_remaining && spi_is_readable(spi)) {
//            *dst++ = (uint8_t) spi_get_hw(spi)->dr;
//            --rx_remaining;
//            num_rx++;
//        }
//        // Check to see if spi send terminated .. if so exit.
//        if (gpio_get(cs_pin)) {
//            //if (num_rx < NUM_BYTES-1) {
//            //    Serial << "exit: " << num_rx << endl;
//            //}
//            break;
//        }
//    }
//    return num_rx;
//}
//
//
//
//void setup() {
//    Serial.begin(115200);
//    spi_init(spi0, SPI_SPEED);
//    gpio_init(SPI_SCK_PIN);
//    gpio_init(SPI_MOSI_PIN);
//    gpio_init(SPI_MISO_PIN);
//    gpio_init(SPI_CS_PIN);
//    gpio_set_function(SPI_MOSI_PIN, GPIO_FUNC_SPI);
//    gpio_set_function(SPI_SCK_PIN, GPIO_FUNC_SPI);
//    gpio_set_function(SPI_MISO_PIN, GPIO_FUNC_SPI);
//    gpio_set_function(SPI_CS_PIN, GPIO_FUNC_SPI);
//    spi_set_slave(spi0, true);
//    spi_set_format(spi0, 8, SPI_CPOL_1, SPI_CPHA_1, SPI_MSB_FIRST);
//
//}
//
//void loop() {
//    static uint32_t count = 0;
//    static uint32_t msg_count = 0;
//    static uint32_t msg_ok_count = 0;
//    static uint32_t msg_short_count = 0;
//    uint8_t data[NUM_BYTES] {0};
//
//    // Read SPI message
//    int num_read = wbd_spi_read_blocking(spi0, 0, data, NUM_BYTES, SPI_CS_PIN);
//    if (num_read < NUM_BYTES-1) {
//        msg_short_count++;
//        //Serial << "short: " << num_read << endl;
//    }
//
//    count++;
//    msg_count++;
//
//    // Check response. Expect 0, 1, 2, ... uint8_t(NUM_BYTES-1)
//    bool msg_test = true;
//    size_t num_bits_set = 0;
//    for (size_t i=0; i<NUM_BYTES; i++) {
//        num_bits_set += std::bitset<sizeof(uint8_t)>(data[i]).count();
//        msg_test = msg_test && (uint8_t(i) == data[i]);
//    }
//    if (msg_test) {
//        msg_ok_count++;
//    }
//
//    if (count < NUM_SKIP) {
//        msg_count = 0;
//        msg_ok_count = 0;
//        msg_short_count = 0;
//    }
//    else {
//        if (msg_count%1000==0) {
//            uint32_t diff = msg_count - msg_ok_count;
//            float frac = float(msg_ok_count)/msg_count;
//            Serial << "msg: " << msg_count << ", ok: " << msg_ok_count;
//            Serial << ", short: " << msg_short_count;
//            Serial << ", diff: " << diff << ", frac: " << frac << endl;;
//        }
//    }
//
//}
