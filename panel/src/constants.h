#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <unordered_map>
#include <Arduino.h>
#include <ArduinoEigen.h>

constexpr size_t  MESSAGE_MAXIMUM_SIZE = 300;
constexpr uint8_t PANEL_SIZE = 20;

// SPI pins
extern const uint8_t SPI_SCK_PIN;
extern const uint8_t SPI_MOSI_PIN;
extern const uint8_t SPI_MISO_PIN;
extern const uint8_t SPI_CS_PIN;

// SPI clock speed (Hz)
extern const uint32_t SPI_SPEED;

// Protocol versions
extern const uint8_t CMD_PROTOCOL_V1;
extern const uint8_t CMD_PROTOCOL;

// Commands (level 1)
extern const uint8_t CMD_ID_COMMS_CHECK;
extern const uint8_t CMD_ID_DISPLAY_GRAY_2;
extern const uint8_t CMD_ID_DISPLAY_GRAY_16;

// Commands (level 2)
extern const uint8_t CMD_ID_QUERY_DIAGNOSTIC;
extern const uint8_t CMD_ID_RESET_DIAGNOSTICS;
extern const uint8_t CMD_ID_RESET_PSRAM;
extern const uint8_t CMD_ID_SET_PSRAM_GRAY_2;
extern const uint8_t CMD_ID_SET_PSRAM_GRAY_16;
extern const uint8_t CMD_ID_DISPLAY_PSRAM;

// Header and payload sizes
extern const size_t HEADER_SIZE;
extern const size_t PAYLOAD_MINIMUM_SIZE;
extern const size_t PAYLOAD_COMMS_CHECK;
extern const size_t PAYLOAD_DISPLAY_GRAY_2;
extern const size_t PAYLOAD_DISPLAY_GRAY_16;
extern const size_t MESSAGE_MINIMUM_SIZE;

using PayloadSizeUMap = std::unordered_map<uint8_t, size_t>;
extern const PayloadSizeUMap PAYLOAD_SIZE_UMAP;

// Led column and row pins
extern const Eigen::Vector<uint8_t, PANEL_SIZE> COL_PIN;
extern const Eigen::Vector<uint8_t, PANEL_SIZE> ROW_PIN; 

// Pattern graylevels
enum class GrayLevel {
    Gray_2, 
    Gray_16, 
};

#endif
