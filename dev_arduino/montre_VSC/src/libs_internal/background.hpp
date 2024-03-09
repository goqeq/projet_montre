#include <Arduino.h>
#include <TFT_eSPI.h>
#include <RTClib.h>

class background{

private:

    void def_init_sprites(TFT_eSprite* sprite, int width, int height, const unsigned short* data, int x, int y);
    void def_init_sprites(TFT_eSprite* sprite, int width, int height, const unsigned short* data);
    void def_init_sprites(TFT_eSprite* sprite, int width, int height);

    void draw_battery(int percentage_local);
    void draw_needle(DateTime now_local);

public:
    void begin();
    void push_background(DateTime now, int percentage);
};