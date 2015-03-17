#ifndef ESP8266_H
#define ESP8266_H

#include "Arduino.h"

class ESP8266{
  public:
    ESP8266();
    void test();
    void contentToWifi(String ssid,String pass);
  private:
};
#endif
