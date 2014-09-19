#include <Arduino.h>
#include "SerialData.h"


SerialData::SerialData()
{
    _readString="";
    _cleanString="";
    _beginStr="{{";
    _endStr="}}";

    _sendBeginString="{{";
    _sendEndString="}}";
};

int SerialData::test()
{
    return 23;
};

void SerialData::setReadLimitString(String bStr,String eStr){
    _beginStr=bStr;
    _endStr=eStr;
};

void SerialData::setSendLimitString(String bStr,String eStr){
    _sendBeginString=bStr;
    _sendEndString=eStr;
};

void SerialData::sendData(String s){
    s=_sendBeginString+s+_sendEndString;
    Serial.print(s);
};

String SerialData::readData(){
    while(Serial.available()>0){
        _readString+=char(Serial.read());
    }
    int beginIndex=_readString.indexOf(_beginStr);
    int endIndex=_readString.indexOf(_endStr);
    if(beginIndex<endIndex&&beginIndex>-1&&endIndex>-1){
        int beginStringLength=_beginStr.length();
        int endStringLength=_endStr.length();
        _cleanString=_readString.substring(beginIndex+beginStringLength,endIndex);
        _readString=_readString.substring(endIndex+endStringLength); 
        return _cleanString;
    }
    return "";
};




Rocker::Rocker(){
     
};


void Rocker::setRockerFun(void (*fun)(String s)){
    _rockerFun=fun;
}

void Rocker::setButtonFun(void (*fun)(String s)){
    _buttonFun=fun;
}

String Rocker::toCommand(String s){
        int aryBegin=s.indexOf("[");
        int aryend=s.indexOf("]");
        String aryString=s.substring(aryBegin+1,aryend);
    if(s.indexOf("Rocker")>-1&&_rockerFun){
        _rockerFun(aryString);
    }else if(s.indexOf("Button")>-1&&_buttonFun){
        _buttonFun(aryString);
    };
    return "abc";
};

RockerData Rocker::parseAry(String s){
        //rockleft:[10,10,10]
    int index=0;
    RockerData rd;
    String tempString="";
    for(int i=0;i<s.length();i++){
        if(s[i]!=','){
            tempString+=s[i];
        }else{
            //int limitIndex=tempString.indexOf(":");
            rd.add(index,tempString);
            tempString="";
            index++;
        }
    }
    return rd;
};

RockerData::RockerData(){

}
void RockerData::add(int index,String s){
    Ary[index]=s;
}







