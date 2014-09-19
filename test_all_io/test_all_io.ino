int testPin=26;
void setup(){
  pinMode(testPin,OUTPUT);
  for(int i=0;i<54;i++){
  pinMode(i,OUTPUT);
  }
}
void loop(){
  for(int i=0;i<54;i++){
     digitalWrite(i,HIGH);
  }
 delay(500);
   for(int i=0;i<54;i++){
     digitalWrite(i,LOW);
  }
  delay(500);
}
