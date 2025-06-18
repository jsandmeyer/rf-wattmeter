/*
=== Raspberry Pi Versions ==============================================================================================

    Release PI1.00  June 28, 2025, John Sandmeyer, AI7YR
                    [Work In Progress]
                    Update to deploy to a less expensive Pi Pico 2 (RP2350) via PlatformIO
                    Uses both cores (Core0 for measuring, Core1 for rendering)
                    Trust Pi Pico ADC range due to lack of good external reference
                    Later: recalculate resistor divider calculation to account for Pi Pico 2

=== Arduino Versions ===================================================================================================

    Release 1.02    February 23, 2024, Bob Fontana, AK3Y
                    Overhaul of display code using display.width and strlen
                    Corrected power calculation code in 2017 W8TEE article
                    Added 3.3V reference adjustment to determine true ADC range
                    Modified resistor divider calculation to provide more accurate measurement

    Release 1.01    June 15, 2018, Jack Purdum, W8TEE. Minor edits to the code to make it easier to read

    Release 1.0     Oct.13, 2017, Jack Purdum, W8TEE, Al Peter, AC8GY. You may use/modify this code,
                    but keep this comment intact in the file and place any changes in front of this
                    entry.
*/

#include <RP2350Wrapper.h> // must include first to avoid warnings
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SerialUSB.h>
#include <can2040.h>
#include <pico/util/queue.h>
#include <Debug.h>

#include "Core0.h"
#include "Core1.h"

#define RP_I2C_USE_I2C0 TRUE

constexpr auto SER_BAUD = 115200UL;

static queue_t wattageQueue;

Adafruit_SSD1306 *display;
Core0 *core0;
Core1 *core1;

void setup() {
    DEBUG(Serial.begin(SER_BAUD));
    DEBUG(Serial.print("Starting core0\n"));

    queue_init(&wattageQueue, sizeof(CAN2040::Message), 128);

    rp2040.fifo.push_nb(0xFFFF);
    DEBUG(Serial.print("Core0 init fifo sent\n"));

    core0 = new Core0(&wattageQueue);
}

void setup1() {
    DEBUG(Serial.print("Starting core1\n"));

    // wait for ready message
    while (rp2040.fifo.pop() != 0xFFFF) {
        tight_loop_contents();
    }

    DEBUG(Serial.print("Core1 init fifo acquired\n"));

    core1 = new Core1(&wattageQueue);
}

void loop() {
    core0->readAdjustor();
    core0->readWattage();
}

void loop1() {
    core1->renderDisplay();
}
