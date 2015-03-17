void setup(){
  pinMode(13,OUTPUT);
  Serial.begin(9600);
}

void loop(){
  while(Serial.available()>0){
    Serial.read();
    digitalWrite(13,HIGH);
  }
  digitalWrite(13,LOW);
  delay(1000);
  byte a=0x11;
  byte b=0x01;
  Serial.print(a,byte);
}  
