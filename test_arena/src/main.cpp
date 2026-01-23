#include <SPI.h>
#include <Streaming.h>
#include <ArduinoEigen.h>
#include "message.h"
#include "pattern.h"

constexpr uint32_t NUM_BYTES = 53; 

const uint8_t  SPI_CS_PIN = 0;
//const uint8_t  SPI_CS_PIN = 2;
//const uint8_t  SPI_CS_PIN = 3;
//const uint8_t  SPI_CS_PIN = 4;
const uint32_t SPI_SPEED = 10000000;


SPISettings spi_settings(SPI_SPEED, MSBFIRST, SPI_MODE3);

void setup() {
    Serial.begin(115200);
    pinMode(SPI_CS_PIN, OUTPUT);
    digitalWrite(SPI_CS_PIN, HIGH);
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
    msg.from_pattern(pat);

    SPI.beginTransaction(spi_settings);
    digitalWrite(SPI_CS_PIN, LOW);
    delayMicroseconds(5);
    SPI.transfer(msg.data_ptr(), msg.num_bytes());
    delayMicroseconds(5);
    SPI.endTransaction();
    digitalWrite(SPI_CS_PIN, HIGH);

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

    delayMicroseconds(1500);

}
