#include <Arduino.h>
#include "libs_internal/background.hpp"
#include "Sprites_data.h"
#include <RTClib.h>

background BackGround;

RTC_DS3231 rtc;

void init(){
  if (!rtc.begin()) {
    Serial.println("Impossible de trouver le RTC");
    while (1);
  }
}

void setup() {
  Serial.begin(9600);

  init();

  BackGround.begin();
}

void loop() {
  int pastMillis = millis();  
  DateTime now = rtc.now(); 

  BackGround.push_background(now, 70);

  int currentMillis = millis();  
  float fps = (1.0/(currentMillis - pastMillis))*1000;
  Serial.println(fps); 
}