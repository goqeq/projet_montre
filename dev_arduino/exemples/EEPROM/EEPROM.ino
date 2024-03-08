#include <Preferences.h>
Preferences prefs;
Preferences prefs2;
String mypassword;
String user;

void setup() {
  Serial.begin(115200);
  prefs.begin("Storage");

  mypassword = prefs.getString("Mypassword", ""); // default to 1
  user = prefs.getString("user", ""); // default to 1
  Serial.print(mypassword);
  Serial.println(user);

  prefs2.begin("Storage1");

  mypassword = prefs2.getString("Mypassword", ""); // default to 1
  user = prefs2.getString("user", ""); // default to 1
  Serial.print(mypassword);
  Serial.println(user);
}

void loop() {}