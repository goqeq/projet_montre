#include <CST816S.h>

CST816S touch(21, 22, 25, 13);	// sda, scl, rst, irq

void setup() {
  Serial.begin(9600);

  touch.begin(RISING);

  Serial.print(touch.data.version);
  Serial.print("\t");
  Serial.print(touch.data.versionInfo[0]);
  Serial.print("-");
  Serial.print(touch.data.versionInfo[1]);
  Serial.print("-");
  Serial.println(touch.data.versionInfo[2]);

}

int touched = 0;
void loop() {
  touched = touch.available();
  if (touched == 1){
    Serial.println(touched);
  }
  else{
    //Serial.println("oui");
  }
}