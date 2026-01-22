#include "constants.h"

// SPI pins
const uint8_t SPI_SCK_PIN = 34;
const uint8_t SPI_MOSI_PIN = 32;
const uint8_t SPI_MISO_PIN = 35;
const uint8_t SPI_CS_PIN = 33;

// SPI clock speed (Hz) 
// Note, I'm just setting it to something higher than what we expect as 
// it doesn't seem to matter what the speed is on the peripheral side. 
const uint32_t SPI_SPEED = 30000000;

// Protocol versions
const uint8_t CMD_PROTOCOL_V1 = 0x01;
const uint8_t CMD_PROTOCOL = CMD_PROTOCOL_V1;

// Commands (level 1)
const uint8_t CMD_ID_COMMS_CHECK = 0x01;
const uint8_t CMD_ID_DISPLAY_GRAY_2 = 0x10;
const uint8_t CMD_ID_DISPLAY_GRAY_16 = 0x30;

// Commands (level 2)
const uint8_t CMD_ID_QUERY_DIAGNOSTIC = 0x02;
const uint8_t CMD_ID_RESET_DIAGNOSTICS = 0x03;
const uint8_t CMD_ID_RESET_PSRAM = 0x0F;
const uint8_t CMD_ID_SET_PSRAM_GRAY_2 = 0x1F;
const uint8_t CMD_ID_SET_PSRAM_GRAY_16 = 0x3F;
const uint8_t CMD_ID_DISPLAY_PSRAM = 0x50;

// Header and payload sizes
const size_t HEADER_SIZE = 2;
const size_t PAYLOAD_MINIMUM_SIZE = 1;
const size_t PAYLOAD_COMMS_CHECK = 200;
const size_t PAYLOAD_DISPLAY_GRAY_2 = 51;
const size_t PAYLOAD_DISPLAY_GRAY_16 =201;
const size_t MESSAGE_MINIMUM_SIZE = HEADER_SIZE + PAYLOAD_MINIMUM_SIZE;

const PayloadSizeUMap PAYLOAD_SIZE_UMAP {
    {CMD_ID_COMMS_CHECK,     PAYLOAD_COMMS_CHECK}, 
    {CMD_ID_DISPLAY_GRAY_2,  PAYLOAD_DISPLAY_GRAY_2},
    {CMD_ID_DISPLAY_GRAY_16, PAYLOAD_DISPLAY_GRAY_16},
};

// LED Column and Row pins
const Eigen::Vector<uint8_t, PANEL_SIZE> COL_PIN 
    {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};

const Eigen::Vector<uint8_t, PANEL_SIZE> ROW_PIN 
    {21,22,23,24,25,26,27,28,29,30,31,36,37,38,39,40,41,42,43,44};
