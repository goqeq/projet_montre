#include <RTClib.h>
#include <CST816S.h>

RTC_DS3231 rtc;
CST816S touch(21, 22, 25, 13);	// sda, scl, rst, irq

void setup() {
  rtc.begin();
  Serial.begin(115200);

  touch.begin();

  Serial.print(touch.data.version);
  Serial.print("\t");
  Serial.print(touch.data.versionInfo[0]);
  Serial.print("-");
  Serial.print(touch.data.versionInfo[1]);
  Serial.print("-");
  Serial.println(touch.data.versionInfo[2]);

}


void loop() {
  DateTime now = rtc.now();

  if (touch.available()) {
    Serial.print(touch.gesture());
    Serial.print("\t");
    Serial.print(touch.data.points);
    Serial.print("\t");
    Serial.print(touch.data.event);
    Serial.print("\t");
    Serial.print(touch.data.x);
    Serial.print("\t");
    Serial.print(touch.data.y);
    Serial.print("\t");
    Serial.print(now.year());
    Serial.print("-");
    Serial.print(now.month());
    Serial.print("-");
    Serial.print(now.day());
    Serial.print(" ");
    Serial.print(now.hour());
    Serial.print(":");
    Serial.print(now.minute());
    Serial.print(":");
    Serial.println(now.second());
  }


}