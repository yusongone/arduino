#include <SoftwareSerial.h>

SoftwareSerial ss(4, 3);

String CMDHead="$GPGGA";
//String CMDHead="$GPRMC";
String heading="";
String CMD="";
bool startCMD=0;
String cleanCMD;

void setup(){
  pinMode(13,OUTPUT);
  Serial.begin(115200);
  ss.begin(9600);
}

void parse(char tempChar){
    if(CMDHead.indexOf(tempChar)>-1){
      heading+=tempChar;
      if(tempChar=='$'&&CMD!=""){
          startCMD=false;
          digitalWrite(13,HIGH);
          cmdToAry(CMD);
      }else if(heading==CMDHead){
        startCMD=true;
      }
    }
    else{
      if(startCMD){
        CMD+=tempChar;
      }else{
        CMD="";
      };
      heading="";
    }
}

  String UTC;
  String lat;
  String lon;
  String ait;
  String star;

void cmdToAry(String str){
  String tempString="";
  int cmdCursor=0;


  for(int i=0;i<str.length();i++){
    char temp=str[i];
    if(temp==','){
      cmdCursor++;
      switch(cmdCursor){
        case 2://lat
          UTC=tempString;
        break;
        case 3://lat
          lat=tempString;
        break;
        case 4://lon
        //  lon=tempString;
        case 5://lon
          lon=tempString;
        case 8://lon
          star=tempString;
        case 10://lon
          ait=tempString;
        break;
      }
      tempString="";
    }else{
      tempString+=str[i]; 
    }
  }
  Serial.print("UTC=");
  Serial.println(UTC);

  Serial.print("lat=");
  Serial.println(lat);

  Serial.print("lon=");
  Serial.println(lon);

  Serial.print("ait=");
  Serial.println(ait);

  Serial.print("star=");
  Serial.println(star);
}

void loop(){
 while(ss.available()){
   char c=ss.read();
   cleanCMD+=c;
 } 
  if(cleanCMD!=""){
   // Serial.println(cleanCMD);
    for(int i=0;i<cleanCMD.length();i++){
      parse(cleanCMD[i]);
    }
    cleanCMD="";
  }
 digitalWrite(13,LOW);
}
