#include <Arduino.h>
#include "myLogger.h"


Debug myDebug("main", Debug::INFO);


void setup() {
  // put your setup code here, to run once:

    {
    Serial.begin(460800);
    Serial.setTimeout(10);
    Serial.println("Boot");
  }
}
bool dp;
void loop() {

    float pi = 3.14159;
    delay(1000);
    myDebug.printName(dp);
    myDebug.printLevel(dp);
    myDebug.printColor(dp);
    myDebug.printLocation(dp);
    dp = !dp;
  log_error(myDebug,"Pi is approximately %0.4f, la mitad es %f",pi, pi/2);

}