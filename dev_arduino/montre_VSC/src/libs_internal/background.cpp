#include "background.hpp"
#include "Sprites_data.h"
#include <RTClib.h>
#include <Arduino.h>
#include <TFT_eSPI.h>

const char* day_of_week[7] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};

TFT_eSPI tft = TFT_eSPI();

#define center_x 120
#define center_y 120
#define TFT_GRIS 0x3186
#define TFT_BLEU 0x2418
#define ColorDepth 8

TFT_eSprite background_sprite = TFT_eSprite(&tft);
TFT_eSprite secondneedle_sprite = TFT_eSprite(&tft);
TFT_eSprite minuteneedle_sprite = TFT_eSprite(&tft);
TFT_eSprite hourneedle_sprite = TFT_eSprite(&tft);
TFT_eSprite thunder_sprite = TFT_eSprite(&tft);

uint16_t TFT_COLORS[6][5] = {
    {TFT_RED, TFT_GRIS, TFT_GRIS, TFT_GRIS, TFT_GRIS},
    {TFT_ORANGE, TFT_GRIS, TFT_GRIS, TFT_GRIS, TFT_GRIS},
    {TFT_BLEU, TFT_BLEU, TFT_GRIS, TFT_GRIS, TFT_GRIS},
    {TFT_BLEU, TFT_BLEU, TFT_BLEU, TFT_GRIS, TFT_GRIS},
    {TFT_BLEU, TFT_BLEU, TFT_BLEU, TFT_BLEU, TFT_GRIS},
    {TFT_BLEU, TFT_BLEU, TFT_BLEU, TFT_BLEU, TFT_BLEU}
};

struct WedgeData {
    int x1;
    int y1;
    int x2;
    int y2;
    int width;
    int length;
};

WedgeData wedgeData[4] = {
  {9, 4, 9, 60, 2, 6},
  {9, 12, 9, 40, 1, 2},
  {9, 4, 9, 100, 2, 6},
  {9, 16, 9, 80, 1, 2}
};

/*   PRIVATE FUNCTION   */

/*   draw_needle*/

void background::draw_needle(DateTime now_local){
  TFT_eSprite* sprite_array[3] = {&minuteneedle_sprite, &hourneedle_sprite, &secondneedle_sprite};

  int timeFactors[3] = {now_local.hour() * 30, now_local.minute() * 6, now_local.second() * 6};

  for (int i=0; i < (sizeof(sprite_array) / sizeof(sprite_array[0]) - 1); i++){
    sprite_array[i]->drawWedgeLine(wedgeData[i*2].x1,wedgeData[i*2].y1,wedgeData[i*2].x2,wedgeData[i*2].y2,wedgeData[i*2].width,wedgeData[i*2].length,TFT_WHITE);
    sprite_array[i]->drawWedgeLine(wedgeData[i*2+1].x1,wedgeData[i*2+1].y1,wedgeData[i*2+1].x2,wedgeData[i*2+1].y2,wedgeData[i*2+1].width,wedgeData[i*2+1].length,TFT_BLACK);
    sprite_array[i]->pushRotated(&background_sprite, timeFactors[i], TFT_BLACK);
  }

  secondneedle_sprite.fillRect(0, 0, 2, 118, TFT_RED);
  secondneedle_sprite.pushRotated(&background_sprite, timeFactors[2], TFT_BLACK);
  background_sprite.fillCircle(center_x, center_y, 6, TFT_RED);
  background_sprite.fillCircle(center_x, center_y, 3, TFT_BLACK);
}

/*   draw_battery   */

void background::draw_battery(int percentage_local) {
  background_sprite.fillSprite(TFT_BLACK);
  background_sprite.pushImage(0,0,240,240, background_data);
  background_sprite.setSwapBytes(false);

  int result = (percentage_local > 80) ? 5 : map(percentage_local, 1, 80, 0, 5);

  for (int i = 0; i < 5; ++i) {
    background_sprite.fillCircle(100 + i * 10, 190, 2, TFT_COLORS[result][i]);
  }

  background_sprite.setSwapBytes(true);
  thunder_sprite.pushToSprite(&background_sprite, 112, 205);
}


/*   def_init_sprites   */

void background::def_init_sprites(TFT_eSprite* sprite, int width, int height, const unsigned short* data, int x, int y){
    sprite->setColorDepth(ColorDepth);

    sprite->createSprite(width, height);
    sprite->fillSprite(TFT_BLACK);

    sprite->setPivot(x,y);

    sprite->setSwapBytes(true);
    sprite->pushImage(0,0, width, height, data);

}

void background::def_init_sprites(TFT_eSprite* sprite, int width, int height, const unsigned short* data){
    sprite->setColorDepth(ColorDepth);

    sprite->createSprite(width, height);
    sprite->fillSprite(TFT_BLACK);

    sprite->setSwapBytes(true);
    sprite->pushImage(0,0, width, height, data);
}

void background::def_init_sprites(TFT_eSprite* sprite, int width, int height){
    sprite->setColorDepth(ColorDepth);

    sprite->createSprite(width, height);
    sprite->fillSprite(TFT_BLACK);
}
/*  PUBLIC FUNCTION */

void background::begin(){
    tft.init();
    def_init_sprites(&background_sprite, 240, 240, background_data);
    def_init_sprites(&thunder_sprite, 16, 16, thunderbolt_data);
    def_init_sprites(&secondneedle_sprite, 10, 140, nullptr, 1, 100);
    def_init_sprites(&minuteneedle_sprite, 20, 110, nullptr, 9, 60);
    def_init_sprites(&hourneedle_sprite, 20, 120, nullptr, 9, 100);
    background_sprite.loadFont(nothing_font);
}

void background::push_background(DateTime now, int percentage){
    draw_battery(percentage);
    background_sprite.drawString(day_of_week[now.dayOfTheWeek()-1], 160, 112);
    background_sprite.drawString(String(now.day()), 210, 112);
    draw_needle(now);
    background_sprite.pushSprite(0, 0);
}
