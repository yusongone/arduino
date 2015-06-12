void setup(){
  pinMode(12,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(5,OUTPUT);

  pinMode(4,INPUT);
  pinMode(5,OUTPUT);


  digitalWrite(12,HIGH);

  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);

  Serial.begin(9600);
}

int i=0;
int count=0;
void loop(){
  count++;
  if(count==50){
    i++;count=0;
  }
  digitalWrite(5,HIGH);
  delayMicroseconds(i); 
  digitalWrite(5,LOW);
  delayMicroseconds(1000-i); 
  i==1000?i=0:i=i;
}
