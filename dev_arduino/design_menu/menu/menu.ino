#include <TFT_eSPI.h>
#include <CST816S.h>

CST816S touch(21, 22, 25, 13);	// sda, scl, rst, irq
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite background = TFT_eSprite(&tft);
TFT_eSprite menu = TFT_eSprite(&tft);

int constant = 0;

/*
0 : NONE
1 :
2 : SWIPE DOWN
3 :\
4 :
5 :
6 :  
*/

void setup() {
  Serial.begin(9600);
  tft.init();
  touch.begin();

  background.setColorDepth(8);
  menu.setColorDepth(8);

  background.createSprite(240, 240);
  menu.createSprite(240,240);
  menu.fillSprite(TFT_GREEN);
  background.fillSprite(TFT_RED);
}

bool locked = false;
int y_position_locked = 0;

void loop() {
  touch.available();

  if (touch.data.points && (touch.data.y <= 50 || constant == 1 || (touch.data.y <= 50))  && !locked){
    background.fillSprite(TFT_RED);
    menu.pushToSprite(&background, 0, -240+touch.data.y);
    constant = 1;
  }
  
  else if (constant == 1){ // le doigt quitte l'écran
      //Serial.println(touch.data.y);
      if (50 < touch.data.y && touch.data.y <= 130){ // remonter
      }
      if (touch.data.y > 130 || touch.data.gestureID == 2){ // descendre
        Is_locked();
      }
      else {
        background.fillSprite(TFT_RED);
      }
    constant = 0;
  }

  if (locked){
    if (y_position_locked > 240){
      y_position_locked = 240;
    }
    Serial.println(y_position_locked);
    menu.pushToSprite(&background, 0, -240+y_position_locked);
    y_position_locked += 40; // augmente la rapidité
  }
  
  background.pushSprite(0,0);
}


void Is_locked(){
  locked = true;
  y_position_locked = touch.data.y;
}