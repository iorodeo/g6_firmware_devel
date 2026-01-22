#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <ArduinoEigen.h>
#include "protocol.h"

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

#endif
