#ifndef RC522_READER_H_
#define RC522_READER_H_

#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

class RfidReader {
public:
  RfidReader();
  void setup(MFRC522* mfrc522);
  String read();
  MFRC522* mfrc522;
private:
  long lastEvent;
  int interval = 300;
  String stringUid;
  String defaultUid = "0";
  void setTag();
  int s = 0;
};

#endif
