#include "ESP8266.h"


ESP8266::ESP8266(){

};

void ESP8266::test(){

};

void ESP8266::contentToWifi(String ssid,String pass){
  Serial.println("AT+CWJAP=\""+ssid+"\",\""+pass+"\"");
}
