#include <SerialUSB.h>
#include <Debug.h>

#include "Core0.h"
#include "pins.h"

#define ADC_MAX                       4095      // Maximum ADC value, see analogReadResolution(12) below

#ifdef X_V33
constexpr auto V33                  = X_V33;
#else
constexpr auto V33                  = 3.255f;    // 3.3V, as measured from Pi Pico 2 (A1)
#endif

#ifdef X_R1
constexpr auto R1                   = X_R1;     // R1 as measured (dummy load resistor)
#else
constexpr auto R1                   = 49.2f;    // R1 as measured (dummy load resistor)
#endif

#ifdef X_R2
constexpr auto R2                   = X_R2;     // R2 as measured (upper divider resistor)
#else
constexpr auto R2                   = 99.39f;   // R2 as measured (upper divider resistor)
#endif

#ifdef X_R3
constexpr auto R3                   = X_R3;     // R3 as measured (lower divider resistor)
#else
constexpr auto R3                   = 2.90f;    // R3 as measured (lower divider resistor)
#endif

#ifdef X_ADC_ITERATIONS
constexpr auto ADC_ITERATIONS       = X_ADC_ITERATIONS;
#else
constexpr auto ADC_ITERATIONS       = 30;
#endif

constexpr auto DIODE_VF_SUM_H       = 1.20;     // Voltage drop from diodes (D1 + D2a + D2b) at or above 1/4
constexpr auto DIODE_VF_SUM_L2      = 0.60;     // Voltage drop from diodes (D1 + D2a + D2b) at or above 1/32
constexpr auto DIODE_VF_SUM_L1      = 0.30;     // Voltage drop from diodes (D1 + D2a + D2b) below 1/32

constexpr auto DIVIDER_RATIO        = (R2 + R3) / R3;   // Resistor divider ratio "𝛿"
constexpr auto POW_MULTIPLIER       = DIVIDER_RATIO * V33 / ADC_MAX;
constexpr auto LOAD_MULTIPLIER      = 2.0f * R1;

Core0::Core0(queue_t* wattageQueue): wattageQueue(wattageQueue) {
    DEBUG(Serial.print("Ready core0\n"));

    adjustmentValue = 0.0f;
    analogReadResolution(12);
}

/**
 * @brief Reads the value of the adjustor pin and calculates the adjustment value.
 *
 * This method reads an analog input from the defined adjustor pin (ADJ_PIN) and calculates an
 * adjustment value based on the input. The calculation scales the raw input value into a
 * defined range between a low, mid, and high value. The adjustment value is linearly interpolated
 * based on the input, where the midpoint of the input range divides scaling into two sections:
 * - For values less than or equal to the midpoint, the adjustment value is scaled between `low` and `mid`.
 * - For values greater than the midpoint, the adjustment value is scaled between `mid` and `high`.
 *
 * The computed adjustment value is stored in the `adjustmentValue` member variable.
 */
void Core0::readAdjustor() {
    const auto adjustorPinValue = static_cast<float>(analogRead(PIN_ADJUSTOR));

    constexpr auto scaleMidpoint = 1024.0f;

    constexpr auto low = 0.9f;
    constexpr auto mid = 1.0f;
    constexpr auto high = 1.1f;

    if (adjustorPinValue <= scaleMidpoint) {
        // Scale down: 0-scaleMidpoint -> low-mid
        adjustmentValue = low + (mid - low) * adjustorPinValue / scaleMidpoint;
    } else {
        // Scale up: scaleMidpoint-4095 -> mid-high
        adjustmentValue = mid + (high - mid) * ((adjustorPinValue - scaleMidpoint) / (scaleMidpoint - 1.0f));
    }
}

float Core0::getDiodeVoltageDrop(const int sensorValue) {
    if (sensorValue < 128) {
        return DIODE_VF_SUM_L1;
    }

    if (sensorValue < 1024) {
        return DIODE_VF_SUM_L2;
    }

    return DIODE_VF_SUM_H;
}

void Core0::readWattage() const {
    auto watts = 0.0f;
    auto sensorValue = 0;
    auto diodeVoltageDrop = 0.0f;

    // From AK3Y's article, use formula P_{IN} = (𝛿V_{A} + V_{D})^{2} / 2R_{LOAD}
    // Run it ADC_ITERATIONS times, then divide by that (average)
    for (auto i = 0; i < ADC_ITERATIONS; i++) {
        sensorValue = analogRead(PIN_SENSOR);

        if (sensorValue > 0) {
            diodeVoltageDrop = getDiodeVoltageDrop(sensorValue);
            watts += max(0, pow(POW_MULTIPLIER * sensorValue * adjustmentValue + diodeVoltageDrop, 2.0f) / LOAD_MULTIPLIER);
        }

        delay(10);
    }

    watts /= ADC_ITERATIONS;

    if (queue_is_full(wattageQueue)) {
        DEBUG(Serial.print("WARNING QUEUE WAS FULL\n"));
        return;
    }

    queue_try_add(wattageQueue, &watts);
    delay(50);
}
