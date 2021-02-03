#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include "RfidReader.h"

RfidReader::RfidReader() {}

void RfidReader::setup(MFRC522 *mfrc522) {
  this->mfrc522 = mfrc522;
  SPI.begin();
  this->mfrc522->PCD_Init();
}

String RfidReader::read() {
  long now = millis();

  if (now - this->lastEvent < this->interval) {
    return String("none");
  }

  this->lastEvent = now;

  this->setTag();

  char charUid[this->stringUid.length() + 1];
  this->stringUid.toCharArray(charUid, this->stringUid.length() + 1);

  if (this->s % 2 > 0 && 0 == strcmp(charUid, "0")) {
    this->s = 0;
    return String("none");
  }

  return this->stringUid;
}

void RfidReader::setTag() {
  // Look for new cards
  if ( ! this->mfrc522->PICC_IsNewCardPresent()) {
    this->stringUid = this->defaultUid;
    return;
  }

  // Select one of the cards
  if ( ! this->mfrc522->PICC_ReadCardSerial()) {
    this->stringUid = this->defaultUid;
    return;
  }

  this->stringUid = "";
  for(int i = 0; i < this->mfrc522->uid.size; i++) {
    this->stringUid += " " + String(this->mfrc522->uid.uidByte[i]);
  }

  // this->mfrc522->PICC_HaltA();
  this->s++;
}
