#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite background = TFT_eSprite(&tft);
TFT_eSprite minuteneedle = TFT_eSprite(&tft);

void setup() {
  tft.init();
  tft.fillScreen(TFT_BLACK);

  // Configuration des sprites
  background.setColorDepth(8);
  background.createSprite(240, 240);
  background.fillSprite(TFT_BLACK);

  minuteneedle.setColorDepth(8);
  minuteneedle.createSprite(20, 30);
  // Utilisation du même paramètre de swap bytes que background
  minuteneedle.fillSprite(TFT_TRANSPARENT);
}

void loop() {
  background.fillSprite(TFT_BLACK);
  minuteneedle.fillSprite(TFT_ORANGE);
  minuteneedle.drawCircle(10, 10, 3, TFT_BLUE);
  minuteneedle.pushToSprite(&background, 120, 120, TFT_ORANGE);
  background.pushSprite(0, 0);
}
