#include <RTClib.h>

RTC_DS3231 rtc;

void setup () {
  Serial.begin(500000);
  Serial.println("Ready to sync");

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

}

void loop () {
  if (Serial.available()){
    String dateString = Serial.readString(); // ex: "2024-02-28 12:30:00"
    int year = dateString.substring(0, 4).toInt();
    int month = dateString.substring(5, 7).toInt();
    int day = dateString.substring(8, 10).toInt();
    int hour = dateString.substring(11, 13).toInt();
    int minute = dateString.substring(14, 16).toInt();
    int second = dateString.substring(17, 19).toInt();

    rtc.adjust(DateTime(year, month, day, hour, minute, second));
    Serial.println("Time set successfully!");
  }

  DateTime now = rtc.now();

  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

  delay(1);
}
