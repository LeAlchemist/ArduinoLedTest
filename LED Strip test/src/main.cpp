#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

namespace {

constexpr int led = PIND2;
constexpr int numpixels = 8;

Adafruit_NeoPixel pixels(numpixels, led, NEO_GRB + NEO_KHZ800);

constexpr unsigned ledcolors[] = {0x000000, 0xff0000, 0x00ff00, 0x0000ff, 0xffff00, 0xff00ff, 0x00ffff, 0xffffff};

}

void setup() {
  // put your setup code here, to run once:
  pixels.begin();
  pixels.clear();
  pixels.show();
}

void led8bit() //shows 8bit led range
{
  pixels.clear();
  pixels.show();
  for (int ledpos = 0; ledpos < 8; ledpos++)
  {
    pixels.setPixelColor(ledpos, ledcolors[ledpos]);
    pixels.show();
  }
}

void ledtrailin()
{
  pixels.clear();
  pixels.show();
  for (int ledpos = 0; ledpos < 8; ledpos++)
  {
    pixels.setPixelColor(ledpos, ledcolors[ledpos]);
    pixels.show();
    delay(500);
  }
}

void ledchaser()
{
  pixels.clear();
  pixels.show();
  for (int ledpos = -8; ledpos < 8; ledpos++)
  {
    pixels.setPixelColor(ledpos, ledcolors[0]);
    pixels.setPixelColor(ledpos+1, ledcolors[1]);
    pixels.setPixelColor(ledpos+2, ledcolors[2]);
    pixels.setPixelColor(ledpos+3, ledcolors[3]);
    pixels.setPixelColor(ledpos+4, ledcolors[4]);
    pixels.setPixelColor(ledpos+5, ledcolors[5]);
    pixels.setPixelColor(ledpos+6, ledcolors[6]);
    pixels.setPixelColor(ledpos+7, ledcolors[7]);
    pixels.show();
    delay(500);
    pixels.clear();
  }
}

void ledblink()
{
  pixels.clear();
  pixels.show();
  for (int blinkcount = 0; blinkcount < 5; blinkcount++)
  {
    for (int ledpos = 0; ledpos < 8; ledpos++)
    {
      pixels.setPixelColor(ledpos, ledcolors[ledpos]);
      pixels.show();
    }
    delay(1000);
      pixels.clear();
      pixels.show();
    delay(1000);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  led8bit();
  delay(1000);
  ledtrailin();
  delay(1000);
  ledchaser();
  delay(1000);
  ledblink();
  delay(1000);
}
