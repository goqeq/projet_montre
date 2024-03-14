/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com
  Based on the NTP Client library example
*********/

#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <RTClib.h>
#include <TFT_eSPI.h>
#include "fonts.h"

#define AA_FONT_SMALL NotoSansBold15
#define AA_FONT_LARGE NotoSansBold36

// Replace with your network credentials
const char* ssid     = "wifi maison";
const char* password = "3B3CA2A0F4";

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite heure = TFT_eSprite(&tft);
RTC_DS3231 rtc;

// Variables to save date and time
String formattedDate;
String dayStamp;
String timeStamp;

void setup() {
  tft.init();
  tft.fillScreen(TFT_BLACK);
  // We can now plot text on screen using the "print" class
  heure.setColorDepth(8);
  heure.createSprite(200, 50);
  heure.fillSprite(TFT_BLACK);
  heure.setSwapBytes(true);
  heure.loadFont(AA_FONT_SMALL);
  heure.setTextColor(TFT_WHITE,TFT_BLACK); 
  heure.setTextSize(3);

  // Initialize Serial Monitor
  Serial.begin(115200);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  timeClient.begin();
  timeClient.setTimeOffset(3600);  // GMT +1 = 3600

  timeClient.update();

  formattedDate = timeClient.getFormattedTime();

  unsigned long epochTime = timeClient.getEpochTime();

  struct tm *ptm = gmtime ((time_t *)&epochTime);

  long currentYear = ptm->tm_year + 1900;
  int currentMonth = ptm->tm_mon + 1;
  int monthDay = ptm->tm_mday;
  int currentHour = timeClient.getHours();
  int currentMinute = timeClient.getMinutes();
  int currentSecond = timeClient.getSeconds();

  rtc.adjust(DateTime(currentYear, currentMonth, monthDay, currentHour, currentMinute, currentSecond));
}
void loop() {
  heure.fillSprite(TFT_BLACK);

  DateTime now = rtc.now();
  
  String format = String(now.year()) + "-" + String(now.month()) + "-" + String(now.day()) + " " + String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());
  Serial.println(format);

  heure.setTextColor(TFT_WHITE, TFT_BLACK);
  heure.drawString(format, 0, 0);
  heure.pushSprite(50,120);
}