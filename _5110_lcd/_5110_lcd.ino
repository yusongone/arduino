#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#include "SerialData.h"
SerialData s;
Rocker rocker;

/*
pin 7,sclk
pin 6, din
pin 5 d/c
pin 4 cs
pin 3 rst
*/
Adafruit_PCD8544 display= Adafruit_PCD8544(7,6,5,4,3);

const int body_max_size=32;
int body_count=3;
int nowDir=1;
int stepSize=2;
int bodySize=2;
long oldTime=0;
int foodTime=0;
int foodX=-1,foodY=-1;
int markX=-1,markY=-1;
int snakeBody[body_max_size][2]={{0,24},{0+stepSize*1,24},{0+stepSize*2,24}};
void setup(){
  //snake.init();
  Serial.begin(9600);
  display.begin();
   display.setContrast(50);
   
   typedef void (*Fun)(String s);
  Fun buttonfun=buttonFun;
  rocker.setButtonFun(buttonfun);
  getFood();
}
void buttonFun(String s){
  RockerData rd=rocker.parseAry(s);
  if(rd.Ary[0].toInt()==1){
     int temp=rd.Ary[1].toInt();
      if(abs(temp-nowDir)!=2){
        nowDir=temp;
      }
  };
  Serial.print(nowDir+"d");
  
}
void loop(){
   String c=s.readData();
  if(c!=""){
    rocker.toCommand(c);
    //s.sendData(c);
  }
  long nowTime=millis();
  if(nowTime-oldTime>250){
    display.clearDisplay();
    oldTime=nowTime;
    getNextPosition();
    
    display.display();
  }
}
void getFood(){
  foodX=int(random(0,42))*2;
  foodY=int(random(0,24))*2;
};
void getNextPosition(){
    int x=snakeBody[0][0];
    int y=snakeBody[0][1];
    int nextX=0;
    int nextY=0;
    switch(nowDir){
        case 0:
            nextX=x;     
            nextY=y-stepSize;     
            break;
        case 1:
            nextX=x+stepSize;     
            nextY=y;     
            break;
        case 2:
            nextX=x;     
            nextY=y+stepSize;     
            break;
        case 3:
            nextX=x-stepSize;     
            nextY=y;     
            break;
    } 
    if(nextX>84){nextX=nextX-84;};
    if(nextY>48){nextY=nextY-48;};
    if(nextX<0){nextX=84+nextX;};
    if(nextY<0){nextY=48+nextY;};
    checkHit(nextX,nextY);
    snakeMove(nextX,nextY);
}
void checkHit(int x,int y){
  if(x==foodX&&y==foodY){
    addBody();
    getFood();
    getMark();
  }
}
void getMark(int x,int y){
  markX=x;
  markY=y;
}
void addBody(){
  snakeBody[body_count][0]=snakeBody[body_count-1][0];
  snakeBody[body_count][1]=snakeBody[body_count-1][1];
  body_count++;
}
void snakeMove(int x,int y){
    for(int i=body_count-1;i>-1;i--){
        if(i>0){
            snakeBody[i][0]=snakeBody[i-1][0];
            snakeBody[i][1]=snakeBody[i-1][1];
        }else{
            snakeBody[i][0]=x;
            snakeBody[i][1]=y;
        }
    }
    drawSnake();
    foodTime++;
    if(foodTime==40){
      getFood();
      foodTime=0;
    }
}

void drawSnake(){
  
  /*
  display.setCursor(38,18);
    display.setTextSize(1);
    display.print(body_count);
    */
  for(int i=0;i<body_count;i++){
    display.fillRect(snakeBody[i][0],snakeBody[i][1],bodySize,bodySize,BLACK);
  }
  if(foodX>-1&&foodY>-1){
    display.fillRect(foodX,foodY,2,2,BLACK);
  }
   if(markX>-1&&markY>-1){
    display.fillRect(foodX-1,foodY-1,4,4,BLACK);
  }
}
