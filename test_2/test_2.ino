volatile int state=LOW;
void setup(){
  pinMode(13,OUTPUT);
  attachInterrupt(0,blink,CHANGE);   
  Serial.begin(9600);
}


void loop(){
 digitalWrite(13,state); 
 Serial.println(digitalRead(2)); 
}

void blink(){
  state=!state;  
}
