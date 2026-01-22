#include "protocol.h"

// Protocol versions
const uint8_t CMD_PROTOCOL_V1 = 0x01;
const uint8_t CMD_PROTOCOL = CMD_PROTOCOL_V1;

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

const DisplayCommandsUMap DISPLAY_COMMANDS_UMAP {
    // for lookup - only care about keys
    {CMD_ID_DISPLAY_GRAY_2,  0},  
    {CMD_ID_DISPLAY_GRAY_16, 0},
};
