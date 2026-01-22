#include <hardware/spi.h>
#include <hardware/gpio.h>
#include "constants.h"
#include "panel_spi_custom.h"

// ------------------------------------------------------------------------------
//
// Customized versino SPI blocking read - based on version in pico SDK. 
//
// This version has modified to help deal with synchronization issues which can
// occur when the panels are hot plugged. In particular the read is terminated
// when the CS pin goes low instead of waiting until all the bytes have been
// read. The enables the reads to reset.  
// 
// ------------------------------------------------------------------------------
int __not_in_flash_func(custom_spi_read_blocking)(
        spi_inst_t *spi, 
        uint8_t    repeated_tx_data, 
        uint8_t    *dst, 
        size_t     len, 
        uint8_t    cs_pin
    ) 
{
    invalid_params_if(HARDWARE_SPI, 0 > (int)len);
    const size_t fifo_depth = 8;
    size_t rx_remaining = len, tx_remaining = len;
    int num_rx = 0;

    // Wait until spi is readable
    while(!spi_is_readable(spi)) {}; 

    while (rx_remaining || tx_remaining) {
        if (tx_remaining && spi_is_writable(spi) && rx_remaining < tx_remaining + fifo_depth) 
        {
            spi_get_hw(spi)->dr = (uint32_t) repeated_tx_data;
            --tx_remaining;
        }
        if (rx_remaining && spi_is_readable(spi)) {
            *dst++ = (uint8_t) spi_get_hw(spi)->dr;
            --rx_remaining;
            num_rx++;
        }
        // Check to see if spi send terminated .. if so exit.
        if (gpio_get(cs_pin)) {
            break;
        }
    }
    return num_rx;
}



void panel_spi_read(Message &msg) {
    msg.num_bytes_ = custom_spi_read_blocking(
            spi0, 
            0, 
            msg.data_.data(), 
            MESSAGE_MAXIMUM_SIZE, 
            SPI_CS_PIN
            );
}
