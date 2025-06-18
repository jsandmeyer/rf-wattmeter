#ifndef CORE1_H
#define CORE1_H

#include <Adafruit_SSD1306.h>
#include <pico/util/queue.h>

class Core1 {
    float lastRenderedWattage = -0.1f;
    Adafruit_SSD1306* display;
    queue_t* wattageQueue;
public:
    explicit Core1(queue_t* wattageQueue);
    void renderDisplay();
};

#endif //CORE1_H
