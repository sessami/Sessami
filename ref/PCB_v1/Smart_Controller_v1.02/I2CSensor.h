#ifndef I2CSENSOR_H_
#define I2CSENSOR_H_

#if (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Wire.h>

#define B0 B00000001 //1
#define B1 B00000010 //2
#define B2 B00000100 //4
#define B3 B00001000 //8
#define B4 B00010000 //16
#define B5 B00100000 //32
#define B6 B01000000 //64
#define B7 B10000000 //128
#define HB 0x100
#define HBMASK 0xFF


typedef bool State;

#define HI true
#define LO false

class I2CSensor
{
  private:
    static bool wire_begin;
    int addr;

  protected:
    int GetAddr() { return addr; }
  public:
    I2CSensor(int _addr);
    ~I2CSensor();

    uint8_t I2CRead();
    void I2CWrite(uint8_t x);
    uint8_t ReadRegister(uint8_t reg);
    uint8_t* ReadRegister(uint8_t reg, uint8_t read_size);
    void WriteRegister(uint8_t reg, uint8_t value);
    void WriteRegBit(uint8_t reg, uint8_t xbit , State st);
    virtual bool initWireI2C() = 0;
};

bool I2CSensor::wire_begin = false;

I2CSensor::I2CSensor(int _addr) : addr(_addr) {
  if (!wire_begin) {
    Wire.begin();
    delay(500);
    wire_begin = true;
  }
}

I2CSensor::~I2CSensor()
{}

#endif
