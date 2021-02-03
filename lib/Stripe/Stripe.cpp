#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#include "Stripe.h"

Stripe::Stripe() {}

void Stripe::setup(Adafruit_NeoPixel *pixels) {
  pixels->begin();
  this->pixels = pixels;
  this->numPixels = this->pixels->numPixels();

  this->actualBrightness = this->brightness;
  this->pixels->setBrightness(this->brightness);
  this->onColor = this->pixels->Color(255, 0, 0);
  this->offColor = this->pixels->Color(0, 0, 0);
  this->color = this->onColor;

  this->pixels->show();
}

void Stripe::loop() {

  if (1 == this->loopType) {
    return this->cycle();
  }

  if (2 == this->loopType) {
    return this->pulsate();
  }

}

void Stripe::cycle() {
  if (this->actualBrightness < this->brightness) {
    this->pixels->setBrightness(this->brightness);
    this->actualBrightness = this->brightness;
  }

  if (this->index >= this->numPixels) {
    this->index = -1;
    // this->pixels->clear();
    if (this->color == this->onColor) {
      this->color = this->offColor;
    } else {
      this->color = this->onColor;
    }
  }

  long now = millis();

  if (now - this->lastEvent < this->interval) {
    return;
  }

  this->lastEvent = now;
  this->index++;

  this->pixels->setPixelColor(this->index, this->color);
  this->pixels->show();
}

void Stripe::pulsate() {
  if (this->index < this->numPixels) {
    return this->cycle();
  }

  long now = millis();

  if (now - this->lastEvent < this->pulseInterval) {
    return;
  }

  this->lastEvent = now;

  if (0 == this->brightnessDirection) {
    if (this->actualBrightness > 0) {
      this->actualBrightness--;
    } else {
      this->pixels->clear();
      this->brightnessDirection = 1;
      return;
    }
  } else {
    if (this->actualBrightness < this->brightness) {
      this->actualBrightness++;
    } else {
      this->actualBrightness--;
      this->brightnessDirection = 0;
    }
  }

  this->pixels->setBrightness(this->actualBrightness);
  this->onForAll();
  this->pixels->show();
}

void Stripe::onForAll() {
  for (int a = 0; a < this->numPixels; a++) {
    this->pixels->setPixelColor(a, this->onColor);
  }
}

void Stripe::setType(int type) {
  if (1 != type && 2 != type) {
    type = 1;
  }
  this->loopType = type;
}
