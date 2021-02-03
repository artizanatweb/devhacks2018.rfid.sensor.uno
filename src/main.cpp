#include <Arduino.h>
#include <MFRC522.h>
#include <Adafruit_NeoPixel.h>
#include "RfidReader.h"
#include "Board.h"
#include "Stripe.h"

#define UNIT_ID (4)
#define SS_PIN (10)
#define RST_PIN (9)
#define PIN (6)
#define NUMPIXELS (14)


MFRC522 mfrc522(SS_PIN, RST_PIN);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
RfidReader reader = RfidReader();
Stripe stripe = Stripe();
Board board = Board(UNIT_ID, &reader, &stripe);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  reader.setup(&mfrc522);

  stripe.setup(&pixels);
  stripe.setType(2);
}

void loop() {
  // put your main code here, to run repeatedly:
  board.send();
}
