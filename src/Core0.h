#ifndef CORE0_H
#define CORE0_H

#include <pico/util/queue.h>

class Core0 {
    queue_t* wattageQueue;
    float adjustmentValue;
public:
    explicit Core0(queue_t* wattageQueue);
    void readAdjustor();
    void readWattage() const;

    static float getDiodeVoltageDrop(int sensorValue);
};


#endif //CORE0_H
