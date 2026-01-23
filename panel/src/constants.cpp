#include "constants.h"

// USB/Serial parameters
const uint32_t BAUDRATE = 115200;

// SPI pins
const uint8_t SPI_SCK_PIN = 34;
const uint8_t SPI_MOSI_PIN = 32;
const uint8_t SPI_MISO_PIN = 35;
const uint8_t SPI_CS_PIN = 33;

// SPI clock speed (Hz) 
// Note, I'm just setting it to something higher than what we expect as 
// it doesn't seem to matter what the speed is on the peripheral side. 
const uint32_t SPI_SPEED = 30000000;

// LED Column and Row pins
const Eigen::Vector<uint8_t, PANEL_SIZE> COL_PIN 
    {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};

const Eigen::Vector<uint8_t, PANEL_SIZE> ROW_PIN 
    {21,22,23,24,25,26,27,28,29,30,31,36,37,38,39,40,41,42,43,44};

// Display parameters
const size_t DISPLAY_QUEUE_SIZE = 5;
const uint8_t NUM_COLOR = 4;
