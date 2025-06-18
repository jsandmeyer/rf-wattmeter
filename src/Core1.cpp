#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Debug.h>
#include <RobotoMono_VariableFont_wght8pt7b.h>
#include <Wire.h>
#include <cmath>

#include "Core1.h"

constexpr auto OLED_W = 128;
constexpr auto OLED_H = 64;
constexpr auto TEXT_W = 10;   // monospace text width for RobotoMono_VariableFont_wght8pt7b
constexpr auto TEXT_H = 13;   // monospace text height for RobotoMono_VariableFont_wght8pt7b
constexpr auto BAR_H  = 22;    // height of bar
constexpr auto BAR_X  = 2;     // margin for bar (used for left, right, bottom)
constexpr auto BAR_Y = OLED_H - BAR_H - BAR_X;
constexpr auto BAR_W  = OLED_W - 2 * BAR_X;

Core1::Core1(queue_t* wattageQueue): wattageQueue(wattageQueue) {
    display = new Adafruit_SSD1306(OLED_W, OLED_H, &Wire); // Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
    display->begin(SSD1306_SWITCHCAPVCC, 0x3C); // Initialize the display

    display->clearDisplay();
    display->setRotation(2);
    display->display();
}

void Core1::renderDisplay() {
    auto wattage = -1.0f;
    char oledText[10];

    // try to get wattage from Core0
    if (!queue_try_remove(wattageQueue, &wattage)) {
        return;
    }

    // do nothing if there's nothing new to render
    if (std::abs(lastRenderedWattage - wattage) < 0.001f) {
        return;
    }

    lastRenderedWattage = wattage;

    // format text - length should be 9 unless something unexpected happened
    const auto oledTextLength = sprintf(oledText, "%7.3f W", wattage);

    // show text
    display->clearDisplay();
    display->setFont(&RobotoMono_VariableFont_wght8pt7b); // 10w 13h
    display->setTextColor(WHITE);
    display->setCursor((OLED_W / 2) - oledTextLength * (TEXT_W / 2), TEXT_H * 2);
    display->print(oledText);

    // show bar graph
    display->drawRect(BAR_X, BAR_Y, BAR_W, BAR_H, WHITE);
    display->fillRect(BAR_X, BAR_Y, static_cast<short>(wattage * BAR_W / 100), BAR_H, WHITE);

    // render
    display->display();
    DEBUG(Serial.println(oledText));
}
