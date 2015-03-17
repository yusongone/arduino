#include <SoftwareSerial.h>

#include "ESP8266.h"

SoftwareSerial mySerial(10, 11); // RX, TX

ESP8266 wifi;

#define SERVER_IP "192.168.100.120"
#define SERVER_PORT "3245"

void setup(){
  delay(1000);
  Serial.begin(57600);
  mySerial.begin(9600);
  mySerial.println("AT+CIPMUX=1");
  delay(2000);
  mySerial.println("AT+CIPSTART=4,\"TCP\",\"192.168.1.106\",4000");
};

void loop(){
  delay(300);
 // mySerial.println("AT+CWMODE=3");
 // mySerial.println("AT+CWJAP=\"xie\",\"ABC501@123\"");
  //mySerial.println("AT+CIFSR");
  String d="";
  while(mySerial.available()>0){
    d+=Serial.print((char)(mySerial.read()));
  }
  
};


