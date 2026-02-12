#include <array>
#include <SPI.h>
#include <Streaming.h>
#include <ArduinoEigen.h>
#include "message.h"
#include "pattern.h"

constexpr uint32_t NUM_BYTES = 53; 
constexpr size_t NUM_CS_PINS = 4;
const uint32_t SPI_SPEED = 25000000;
const std::array<uint8_t,NUM_CS_PINS> SPI_CS_PINS {0,2,3,4};

//const std::array<uint8_t,NUM_CS_PINS> SPI_CS_PINS {2,3,4,0};
//const std::array<uint8_t,NUM_CS_PINS> SPI_CS_PINS {3,4,0,2};
//const uint8_t  SPI_CS_PIN = 0;
//const uint8_t  SPI_CS_PIN = 2;
//const uint8_t  SPI_CS_PIN = 3;
//const uint8_t  SPI_CS_PIN = 4;


SPISettings spi_settings(SPI_SPEED, MSBFIRST, SPI_MODE3);

void setup() {
    Serial.begin(115200);
    for (auto cs_pin : SPI_CS_PINS) {
        pinMode(cs_pin, OUTPUT);
        digitalWrite(cs_pin, HIGH);
    }
    SPI.begin();
}

void loop() {

    static uint32_t count = 0;
    static uint32_t pos = 0;
    static bool increasing = true;

    Pattern pat;
    pat.set_gray_level(GrayLevel::Gray_2);
    pat.set_stretch(255);

    for (size_t j=0; j<PANEL_SIZE; j++) {
        pat.matrix()(pos,j) = 1;
        pat.matrix()(j,pos) = 1;
    }
    
    Message msg; 
    for (auto cs_pin : SPI_CS_PINS) {
        msg.from_pattern(pat);
        SPI.beginTransaction(spi_settings);
        digitalWrite(cs_pin, LOW);
        delayMicroseconds(5);
        SPI.transfer(msg.data_ptr(), msg.num_bytes());
        delayMicroseconds(5);
        SPI.endTransaction();
        digitalWrite(cs_pin, HIGH);
        delayMicroseconds(5);
    }

    if (count%25 == 0) {
        if (increasing) {
            pos = pos + 1;
            if (pos == PANEL_SIZE-1) {
                increasing = false;
            }
        }
        else {
            pos = pos - 1;
            if (pos==0) {
                increasing = true;
            }
        }
        Serial << "count: " << count << ", pos: " << pos << endl;
    }
    count++;

    delayMicroseconds(1000);

}
