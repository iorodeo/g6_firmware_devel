#include <Streaming.h>
#include "pico/util/queue.h"
#include "constants.h"
#include "messenger.h"
#include "pattern.h"
#include "display.h"

queue_t display_queue;

// Core 0
// -----------------------------------------------------------------------
Messenger messenger(display_queue);
void setup() {
    Serial.begin(BAUDRATE);
    queue_init(&display_queue, sizeof(Pattern), DISPLAY_QUEUE_SIZE);
    messenger.initialize();
}

void loop() {
    messenger.update();
}


// Core 1
// -----------------------------------------------------------------------
bool core1_separate_stack = true;
Display display(display_queue);

void setup1() {
    display.initialize();
}

void loop1() {
    display.update();
}


