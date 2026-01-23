#ifndef PROTOCOL_H
#define PROTOCOL_H
#include <unordered_map>
#include <Arduino.h>

// Protocol versions
extern const uint8_t CMD_PROTOCOL_V1;
extern const uint8_t CMD_PROTOCOL;

enum CommandId: uint8_t {
    // Commands (level 1)
    CMD_ID_COMMS_CHECK       = 0x01,
    CMD_ID_DISPLAY_GRAY_2    = 0x10,
    CMD_ID_DISPLAY_GRAY_16   = 0x30,

    // Commands (level 2)
    CMD_ID_QUERY_DIAGNOSTIC  = 0x02,
    CMD_ID_RESET_DIAGNOSTICS = 0x03,
    CMD_ID_RESET_PSRAM       = 0x0F,
    CMD_ID_SET_PSRAM_GRAY_2  = 0x1F,
    CMD_ID_SET_PSRAM_GRAY_16 = 0x3F,
    CMD_ID_DISPLAY_PSRAM     = 0x50,
};

constexpr size_t  MESSAGE_MAXIMUM_SIZE = 300;
constexpr uint8_t PANEL_SIZE = 20;

// Header and payload sizes
extern const size_t HEADER_SIZE;
extern const size_t PAYLOAD_MINIMUM_SIZE;
extern const size_t PAYLOAD_COMMS_CHECK;
extern const size_t PAYLOAD_DISPLAY_GRAY_2;
extern const size_t PAYLOAD_DISPLAY_GRAY_16;
extern const size_t MESSAGE_MINIMUM_SIZE;

using PayloadSizeUMap = std::unordered_map<uint8_t, size_t>;
extern const PayloadSizeUMap PAYLOAD_SIZE_UMAP;

using DisplayCommandsUMap = std::unordered_map<uint8_t, uint8_t>;
extern const DisplayCommandsUMap DISPLAY_COMMANDS_UMAP;

// Pattern graylevels
constexpr size_t MAX_GRAY_LEVEL = 16;
enum class GrayLevel {
    Gray_2, 
    Gray_16, 
};
using GrayLevelUMap = std::unordered_map<GrayLevel, uint8_t>;
extern const GrayLevelUMap GRAY_LEVEL_UMAP;

#endif
