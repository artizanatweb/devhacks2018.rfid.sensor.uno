#include <Arduino.h>
#include <ArduinoJson.h>
#include "Board.h"
#include "RfidReader.h"
#include "Stripe.h"

Board::Board() {}

Board::Board(int unitId, RfidReader *reader, Stripe* leds) {
  this->unitId = unitId;
  this->reader = reader;
  this->leds = leds;
}

void Board::send() {
  this->leds->loop();

  long now = millis();

  if (now - this->lastEvent < this->interval) {
    return;
  }
  this->lastEvent = now;

  this->tag = this->reader->read();

  char charUid[this->tag.length() + 1];
  this->tag.toCharArray(charUid, this->tag.length() + 1);
  if (0 == strcmp(charUid, "none")) {
    return;
  }

  if (0 == strcmp(charUid, "0")) {
    this->leds->setType(1);
  } else {
    this->leds->setType(2);
  }

  StaticJsonBuffer<255> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  root["unit_id"] = this->unitId;
  root["tag"] = this->tag;
  // root["tag"] = 0;

  root.printTo(Serial);
  // root.prettyPrintTo(Serial);
  Serial.println();
}
