#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

namespace {

constexpr int led = PIND2;
constexpr int numpixels = 8;

Adafruit_NeoPixel pixels(numpixels, led, NEO_GRB + NEO_KHZ800);

constexpr unsigned long ledcolors[] = {0x000000, 0xff0000, 0x00ff00, 0x0000ff,
                                       0xffff00, 0xff00ff, 0x00ffff, 0xffffff};

}  // namespace

void setup() {
    pixels.begin();
    pixels.clear();
    pixels.show();
}

// shows 8bit led range
void led8bit() {
    pixels.clear();
    pixels.show();
    for (unsigned short ledpos = 0; ledpos < 8; ledpos++) {
        pixels.setPixelColor(ledpos, ledcolors[ledpos]);
        pixels.show();
    }
}

void ledtrailing() {
    pixels.clear();
    pixels.show();
    for (unsigned short ledpos = 0; ledpos < 8; ledpos++) {
        pixels.setPixelColor(ledpos, ledcolors[ledpos]);
        pixels.show();
        delay(500);
    }
}

void ledchaser() {
    pixels.clear();
    pixels.show();
    for (short ledpos = -8; ledpos < 8; ledpos++) {
#pragma GCC unroll 8
        for (short i = 0; i < 8; ++i) {
            // When `ledpos` is negative, the bit-cast underflows to a large
            // value. `setPixelColor()` does nothing if while the index is
            // larger that 8.
            pixels.setPixelColor(__builtin_bit_cast(unsigned short, ledpos + i),
                                 ledcolors[i]);
        }
        pixels.show();
        delay(500);
        pixels.clear();
    }
}

void ledblink() {
    pixels.clear();
    pixels.show();
    for (int blinkcount = 0; blinkcount < 5; blinkcount++) {
        for (unsigned short ledpos = 0; ledpos < 8; ledpos++) {
            pixels.setPixelColor(ledpos, ledcolors[ledpos]);
            pixels.show();
        }
        delay(1000);
        pixels.clear();
        pixels.show();
        delay(1000);
    }
}

// Main code that is ran repeatedly.
void loop() {
    led8bit();
    delay(1000);
    ledtrailing();
    delay(1000);
    ledchaser();
    delay(1000);
    ledblink();
    delay(1000);
}
