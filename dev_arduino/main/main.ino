#include <TFT_eSPI.h>
#include "Sprites_data.h"
#include <Wire.h>
#include <RTClib.h>
#include <WiFi.h>

RTC_DS3231 rtc;
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite background = TFT_eSprite(&tft);
TFT_eSprite secondneedle = TFT_eSprite(&tft);
TFT_eSprite minuteneedle = TFT_eSprite(&tft);
TFT_eSprite hourneedle = TFT_eSprite(&tft);
TFT_eSprite hour_screen = TFT_eSprite(&tft);
TFT_eSprite thunderbolt = TFT_eSprite(&tft);

#define center_x 120
#define center_y 120
#define diameter 119
#define TFT_GRIS 0x3186
#define TFT_BLEU 0x2418

float xpos_past, ypos_past, angle, xpos, ypos;
float xpos_past_2, ypos_past_2, angle_2, xpos_2, ypos_2;

String day_of_week[7] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};

void def_init(TFT_eSprite* sprite, int width, int height, const unsigned short* data = nullptr, int x=-1, int y=-1){
  sprite->setColorDepth(8);

  sprite->createSprite(width, height);
  sprite->fillSprite(TFT_BLACK);

  if (y != -1){
    sprite->setPivot(x,y);
  }

  if (data != nullptr){
    sprite->setSwapBytes(true);
    sprite->pushImage(0,0, width, height, data);
  }
}

void init(){
  if (!rtc.begin()) {
    Serial.println("Impossible de trouver le RTC");
    while (1);
  }
}

void setup() {
  Serial.begin(9600);

  init();

  tft.init();
  tft.fillScreen(TFT_BLACK);

  def_init(&background, 240, 240, background_data);
  def_init(&thunderbolt, 16, 16, thunderbolt_data);
  def_init(&secondneedle, 10, 140, nullptr, 1, 100);
  def_init(&minuteneedle, 20, 110, nullptr, 9, 60);
  def_init(&hourneedle, 20, 120, nullptr, 9, 100);
  def_init(&hour_screen, 80, 50);
  background.loadFont(nothing_font);
  hour_screen.setTextColor(TFT_WHITE,TFT_BLACK); 
}

void loop() {
  battery_draw(20);

  DateTime now = rtc.now(); 

  background.drawString(day_of_week[now.dayOfTheWeek()-1], 160, 112);
  background.drawString(String(now.day()), 210, 112);
  drawTime(now);

  background.pushSprite(0, 0);
}

void drawTime(DateTime now){
  TFT_eSprite* sprite_array[] = {&minuteneedle, &hourneedle, &secondneedle};
  int timeFactors[] = {now.hour() * 30, now.minute() * 6, now.second() * 6};

  struct WedgeData {
    int x1;
    int y1;
    int x2;
    int y2;
    int width;
    int length;
  };
  
  WedgeData wedgeData[] = {
    {9, 4, 9, 60, 2, 6},
    {9, 12, 9, 40, 1, 2},
    {9, 4, 9, 100, 2, 6},
    {9, 16, 9, 80, 1, 2}
  };

  for (int i=0; i < (sizeof(sprite_array) / sizeof(sprite_array[0]) - 1); i++){
    sprite_array[i]->drawWedgeLine(wedgeData[i*2].x1,wedgeData[i*2].y1,wedgeData[i*2].x2,wedgeData[i*2].y2,wedgeData[i*2].width,wedgeData[i*2].length,TFT_WHITE);
    sprite_array[i]->drawWedgeLine(wedgeData[i*2+1].x1,wedgeData[i*2+1].y1,wedgeData[i*2+1].x2,wedgeData[i*2+1].y2,wedgeData[i*2+1].width,wedgeData[i*2+1].length,TFT_BLACK);
    sprite_array[i]->pushRotated(&background, timeFactors[i], TFT_BLACK);
  }

  secondneedle.fillRect(0, 0, 2, 118, TFT_RED);
  secondneedle.pushRotated(&background, timeFactors[2], TFT_BLACK);
  background.fillCircle(center_x, center_y, 6, TFT_RED);
  background.fillCircle(center_x, center_y, 3, TFT_BLACK);
}

void battery_draw(int pourcentage) {
  background.fillSprite(TFT_BLACK);
  background.pushImage(0,0,240,240, background_data);
  background.setSwapBytes(false);

  int result = (pourcentage > 80) ? 5 : map(pourcentage, 1, 80, 0, 5);

  uint16_t TFT_COLORS[6][5] = {
    {TFT_RED, TFT_GRIS, TFT_GRIS, TFT_GRIS, TFT_GRIS},
    {TFT_ORANGE, TFT_GRIS, TFT_GRIS, TFT_GRIS, TFT_GRIS},
    {TFT_BLEU, TFT_BLEU, TFT_GRIS, TFT_GRIS, TFT_GRIS},
    {TFT_BLEU, TFT_BLEU, TFT_BLEU, TFT_GRIS, TFT_GRIS},
    {TFT_BLEU, TFT_BLEU, TFT_BLEU, TFT_BLEU, TFT_GRIS},
    {TFT_BLEU, TFT_BLEU, TFT_BLEU, TFT_BLEU, TFT_BLEU}
  };

  for (int i = 0; i < 5; ++i) {
    background.fillCircle(100 + i * 10, 190, 2, TFT_COLORS[result][i]);
  }

  background.setSwapBytes(true);
  thunderbolt.pushToSprite(&background, 112, 205);
}

