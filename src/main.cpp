#include <Arduino.h>
#include "superLogger.h"

Debug myDebug("main",Serial, Debug::INFO);

void setup()
{
  Serial.begin(460800);
}

void loop()
{

  static bool dp;

  myDebug.printName(dp);
  myDebug.printLevel(dp);
  myDebug.printColor(dp);
  myDebug.printLocation(dp);
  
  log_verbose(myDebug,"Testing  printf formats: Integer: %d Float: %f Char: %c String: %s Hexadecimal: %x Octal: %o Scientific : %e Padding  zeroes: %06d Left-justified: %-15s", 123, 3.14, 'A', "Hello World!", 123, 123, 3.14, 123, "Hello World!");
  log_info(myDebug,"Testing  printf formats: Integer: %d Float: %f Char: %c String: %s Hexadecimal: %x Octal: %o Scientific : %e Padding  zeroes: %06d Left-justified: %-15s", 123, 3.14, 'A', "Hello World!", 123, 123, 3.14, 123, "Hello World!");
  log_debug(myDebug,"Testing  printf formats: Integer: %d Float: %f Char: %c String: %s Hexadecimal: %x Octal: %o Scientific : %e Padding  zeroes: %06d Left-justified: %-15s", 123, 3.14, 'A', "Hello World!", 123, 123, 3.14, 123, "Hello World!");
  log_warning(myDebug,"Testing  printf formats: Integer: %d Float: %f Char: %c String: %s Hexadecimal: %x Octal: %o Scientific : %e Padding  zeroes: %06d Left-justified: %-15s ", 123, 3.14, 'A', "Hello World!", 123, 123, 3.14, 123, "Hello World!");
  log_error(myDebug,"Testing  printf formats: Integer: %d Float: %f Char: %c String: %s Hexadecimal: %x Octal: %o Scientific : %e Padding  zeroes: %06d Right-justified: %-15s ", 123, 3.14, 'A', "Hello World!", 123, 123, 3.14, 123, "Hello World!");


  myDebug.setLevel(Debug::VERBOSE);

  dp = !dp;
  delay(1000);
}