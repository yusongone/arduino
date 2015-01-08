#ifndef Protocol_h
#define Protocol_h

#include "Arduino.h"
#include "robot.h"

    void initSerial();
    void reciveCMD();
    void switchCMD();
    boolean checkSum();
    void setRAWData();
    uint8_t read8(int index);
    uint16_t read16(int index);
    uint32_t read32(int index);

#endif
