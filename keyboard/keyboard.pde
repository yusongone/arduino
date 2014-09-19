import processing.serial.*;

Serial serial;
void setup(){
  background(0);
  size(1500,500);
  serial=new Serial(this,"COM7",9600);
}

void draw(){
}
void keyPressed() {
   if(key=='4'){
     serial.write("{{Rocker:[1,3,]}}");
   }else if(key=='5'){
     serial.write("{{Rocker:[1,2,]}}");
   }else if(key=='8'){
     serial.write("{{Rocker:[1,0,]}}");
   }else if(key=='6'){
     serial.write("{{Rocker:[1,1,]}}");
   };
}



