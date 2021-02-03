#ifndef STRIPE_H_
#define STRIPE_H_

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

class Stripe {
public:
  Stripe();
  void setup(Adafruit_NeoPixel* pixels);
  void loop();
  void setType(int type);
private:
  Adafruit_NeoPixel* pixels;
  long lastEvent;
  int interval = 50;
  int pulseInterval = 30;
  int index = -1;
  int numPixels;
  uint32_t onColor;
  uint32_t offColor;
  uint32_t color;
  uint16_t brightness = 30;
  int actualBrightness;
  int brightnessDirection = 0;
  void cycle();
  void pulsate();
  int loopType = 2; // 1 => "cycle", 2 => "pulsate"
  void onForAll();
};

#endif
