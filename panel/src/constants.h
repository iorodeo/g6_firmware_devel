#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <unordered_map>
#include <Arduino.h>
#include <ArduinoEigen.h>

constexpr size_t  SPI_BUFF_SIZE = 300;
constexpr uint8_t PANEL_SIZE = 20;

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

// SPI Commands (level 1)
extern const uint8_t CMD_ID_COMMS_CHECK;
extern const uint8_t CMD_ID_DISPLAY_GRAY_2;
extern const uint8_t CMD_ID_DISPLAY_GRAY_16;

// SPI Commands (level 2)
extern const uint8_t CMD_ID_QUERY_DIAGNOSTIC;
extern const uint8_t CMD_ID_RESET_DIAGNOSTICS;
extern const uint8_t CMD_ID_RESET_PSRAM;
extern const uint8_t CMD_ID_SET_PSRAM_GRAY_2;
extern const uint8_t CMD_ID_SET_PSRAM_GRAY_16;
extern const uint8_t CMD_ID_DISPLAY_PSRAM;

// Payload sizes
extern const size_t PAYLOAD_COMMS_CHECK;
extern const size_t PAYLOAD_DISPLAY_GRAY_2;
extern const size_t PAYLOAD_DISPLAY_GRAY_16;

extern const std::unordered_map<uint8_t, size_t> payload_bytes_;

enum class GrayLevel {
    None,
    GRAY_2, 
    GRAY_16, 
};

#endif
