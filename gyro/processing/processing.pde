import processing.serial.*;

Serial serial;
Line l1;
Line l2;
Line l3;
double P=9000;
double I=0;
double D=0;
void setup(){
  background(0);
  size(1500,700);
  //serial=new Serial(this,"/dev/tty.usbmodem1421",9600);
  //serial=new Serial(this,"/COM7",9600);
 serial=new Serial(this,"/COM7",9600);
  //println(Serial.list());
  l1=new Line(250,0,0);
  l2=new Line(0,255,0);
  l3=new Line(0,0,255);
}

void draw(){
  readData();
}
void keyPressed() {
   if(key=='7'){
     serial.write("{{Rocker:[0,"+(P-=10)+",]}}");    
 }else if(key=='8'){
     serial.write("{{Rocker:[0,"+(P+=10)+",]}}");
   }else if(key=='4'){
     serial.write("{{Rocker:[1,"+(I-=1)+",]}}");
   }else if(key=='5'){
     serial.write("{{Rocker:[1,"+(I+=1)+",]}}");
   }else if(key=='1'){
     serial.write("{{Rocker:[2,"+(D-=1)+",]}}");
   }else if(key=='2'){
     serial.write("{{Rocker:[2,"+(D+=1)+",]}}");
   };
}
String _readString="";
String readData(){
  String _beginStr="{{";
  String _endStr="}}";
  String _cleanString="";
  while(serial.available()>0){
    
        _readString+=char(serial.read());
    }
    int beginIndex=_readString.indexOf(_beginStr);
    int endIndex=_readString.indexOf(_endStr);
    if(beginIndex<endIndex&&beginIndex>-1&&endIndex>-1){
        int beginStringLength=_beginStr.length();
        int endStringLength=_endStr.length();
        _cleanString=_readString.substring(beginIndex+beginStringLength,endIndex);
        _readString=_readString.substring(endIndex+endStringLength); 
        toCommand(_cleanString);
        return _cleanString;
    }
    return "";
}

  int x=0;
void toCommand(String s){
        int aryBegin=s.indexOf("[");
        int aryend=s.indexOf("]");
        String aryString=s.substring(aryBegin+1,aryend);
    if(s.indexOf("Rocker")>-1){
        String[] zhou=split(aryString,",");
        x+=2;
        if(!(x<1500)){
          x=0;
        }
        l1.draw(x,parseInt(zhou[0]));
        l2.draw(x,parseInt(zhou[1]));
        l3.draw(x,parseInt(zhou[2]));
        stroke(255,255,255);
        line(0,350,1500,350);
        line(0,100,1500,100);
        line(0,600,1500,600);
        textSize(32);
        fill(0,0,0);
        rect(10,0,150,30);
        fill(0, 102, 153);
        text("P:"+(P/100), 10, 30); 
        fill(0,0,0);
        rect(200,0,150,30);
        fill(0, 102, 153);
        text("I:"+(I/100), 210, 30); 
        fill(0,0,0);
        rect(400,0,150,30);
        fill(0, 102, 153);
        text("D:"+(D/100), 410, 30); 
        fill(0, 102, 153);
        if(x==0){
          background(0);
        }
         
        
       
    }else if(s.indexOf("Button")>-1){
        //_buttonFun(aryString);
    };
};

class Line{
  int mid=350;
  int oldY=mid;
  int oldX=0;
  int _r,_g,_b;
  Line(int r,int g,int b){
    _r=r;
    _g=g;
    _b=b;
  }
  void draw(int x,int y){
    stroke(_r,_g,_b);
    y+=mid;
    line(oldX,oldY,x,y);
    oldY=y;
    oldX=x;
  }
}


