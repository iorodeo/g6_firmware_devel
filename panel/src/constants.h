#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <ArduinoEigen.h>
#include "protocol.h"

// USB/Serial parameters
extern const uint32_t BAUDRATE;

// SPI pins
extern const uint8_t SPI_SCK_PIN;
extern const uint8_t SPI_MOSI_PIN;
extern const uint8_t SPI_MISO_PIN;
extern const uint8_t SPI_CS_PIN;

// SPI clock speed (Hz)
extern const uint32_t SPI_SPEED;

// Led column and row pins
extern const Eigen::Vector<uint8_t, PANEL_SIZE> COL_PIN;
extern const Eigen::Vector<uint8_t, PANEL_SIZE> ROW_PIN; 

// Display parameters
extern const size_t DISPLAY_QUEUE_SIZE;
extern const uint8_t NUM_COLOR;


#endif
