#include <SPI.h>
#include <Streaming.h>
#include <ArduinoEigen.h>

constexpr uint32_t NUM_BYTES = 53; 

const uint8_t  SPI_CS_PIN = 0;
//const uint8_t  SPI_CS_PIN = 2;
//const uint8_t  SPI_CS_PIN = 3;
//const uint8_t  SPI_CS_PIN = 4;
const uint32_t SPI_SPEED = 10000000;


// SPI Commands (level 1)
const uint8_t CMD_ID_COMMS_CHECK = 0x01;
const uint8_t CMD_ID_DISPLAY_GRAY_2 = 0x10;
const uint8_t CMD_ID_DISPLAY_GRAY_16 = 0x30;



SPISettings spi_settings(SPI_SPEED, MSBFIRST, SPI_MODE3);



void setup() {
    Serial.begin(115200);
    pinMode(SPI_CS_PIN, OUTPUT);
    digitalWrite(SPI_CS_PIN, HIGH);
    SPI.begin();
}

void loop() {
    static uint32_t count = 0;
    static uint8_t data[NUM_BYTES] {0};

    data[1] = CMD_ID_COMMS_CHECK;

    for (size_t i=0; i<NUM_BYTES; i++) {
        data[i] =  uint8_t(i);
    }

    SPI.beginTransaction(spi_settings);
    digitalWrite(SPI_CS_PIN, LOW);
    delayMicroseconds(5);
    SPI.transfer(data, NUM_BYTES);
    delayMicroseconds(5);
    SPI.endTransaction();
    digitalWrite(SPI_CS_PIN, HIGH);

    if (count%500 == 0) {
        Serial << "count: " << count << endl;
    }
    count++;

    delayMicroseconds(2000);

}
