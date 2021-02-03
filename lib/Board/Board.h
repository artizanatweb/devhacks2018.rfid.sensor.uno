#ifndef BOARD_H_
#define BOARD_H_

#include <Arduino.h>
#include <ArduinoJson.h>
#include "RfidReader.h"
#include "Stripe.h"

class Board {
public:
  Board();
  Board(int unitId, RfidReader* reader, Stripe* leds);
  void send();
private:
  int unitId;
  long lastEvent;
  int interval = 100;
  RfidReader* reader;
  String tag;
  Stripe* leds;
};

#endif
