#include <TFT_eSPI.h>
#include <CST816S.h>

CST816S touch(21, 22, 25, 13);	// sda, scl, rst, irq
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite background = TFT_eSprite(&tft);
TFT_eSprite menu = TFT_eSprite(&tft);

bool constant = false, locked = constant;

int y_position_locked = 0;

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

void loop() {
  touch.available();

  if (touch.data.points && (touch.data.y <= 50 || constant == 1) && !locked){
    y_position_locked = touch.data.y;
    background.fillSprite(TFT_RED);
    menu.pushToSprite(&background, 0, -240+touch.data.y);
    constant = 1;
  }

  else{
    locked = false;

    if (touch.data.y < 130 && constant == 1){
      background.fillSprite(TFT_RED); 
    }

    else if (touch.data.y >= 130 || touch.data.gestureID == 2){
      Is_Locked();
    }

    constant = 0;
  }

  background.pushSprite(0,0);
}


void Is_Locked(){
  locked = true;
  y_position_locked += 40; // rapidité de défilement

  if (y_position_locked >= 240){
    y_position_locked = 240;
  }

  menu.pushToSprite(&background, 0, -240+y_position_locked);
}

