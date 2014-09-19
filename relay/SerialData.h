#include <Arduino.h>

#ifndef SerialData_h
#define SerialData_h


class SerialData
{
  public:
    SerialData();
    int test();
    void setReadLimitString(String s,String b);
    void setSendLimitString(String s,String b);
    void sendData(String s);
    String readData();
  private:
    String _readString; 
    String _cleanString;
    String _beginStr; 
    String _endStr; 
    String _sendBeginString;
    String _sendEndString;

};

class RockerData{
    public:
        RockerData();
        void add(int index,String s);
        String Ary[10];
    private:
};


class Rocker
{
    public:
        Rocker();
        void setFun(void (*fun)(String s));
        void setRockerFun(void (*fun)(String s));
        void setButtonFun(void (*fun)(String s));
        String toCommand(String s);
        RockerData parseAry(String s);
    private:
        typedef void (*test)(String s);
        test _rockerFun;
        test _buttonFun;

};



#endif
