#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "dht.h"

dht DHT;
Adafruit_PCD8544 display= Adafruit_PCD8544(7,6,5,4,3);
float value=0;
int count=0;

void setup(){
  //snake.init();
  pinMode(8,OUTPUT);
  digitalWrite(8,HIGH);
   pinMode(9,OUTPUT);
  digitalWrite(9,HIGH);
   pinMode(10,OUTPUT);
  digitalWrite(10,LOW);
  Serial.begin(115200);
  display.begin();
  display.setContrast(50);
  
  
  
}

void loop(){
   float c=analogRead(4);
  //float new_value=c/1024*5*0.5*1000;

  value=value+c;
  if(count==50){
    //.println(finaly);
    Serial.print("{");
  Serial.print(value/count/1024*4.6*0.35*500);
  Serial.print("}");
     display.clearDisplay();
  display.setCursor(0,0);
    display.setTextSize(1);
    display.print("PM2.5: ");
    display.println(value/count);
    //display.setCursor(0,30);
    
    int chk = DHT.read11(11);
  switch (chk)
  {
    case DHTLIB_OK:  
		//display.print("OK,\t"); 
        display.print("H: ");
        display.println(DHT.humidity);
        display.print("T: ");
        display.println(DHT.temperature);
        break;
    case DHTLIB_ERROR_CHECKSUM: 
	display.print("Checksum error,\t"); 
	break;
    case DHTLIB_ERROR_TIMEOUT: 
	display.print("Time out error,\t"); 
	break;
    default: 
	display.print("Unknown error,\t"); 
	break;
  }
  display.display();
  count=0;
  value=0;
  }
  count++;
  delay(50);
}
