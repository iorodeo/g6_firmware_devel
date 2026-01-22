#include <Streaming.h>
#include "constants.h"
#include "messenger.h"


// Core 0
// -----------------------------------------------------------

Messenger messenger;

void setup() {
    Serial.begin(115200);
    messenger.initialize();
}

void loop() {
    messenger.update();
}


// Core 1
// -----------------------------------------------------------
bool core1_separate_stack = true;

void setup1() {
}

void loop1() {
    delay(100);
}


