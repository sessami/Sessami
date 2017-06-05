#include "I2CSensor.h"

/**************************************************************************/
/*!
    @brief  Abstract away platform differences in Arduino wire library
*/
/**************************************************************************/
uint8_t I2CSensor::I2CRead() {
#if ARDUINO >= 100
  return Wire.read();
#else
  return Wire.receive();
#endif
}

/**************************************************************************/
/*!
    @brief  Abstract away platform differences in Arduino wire library
*/
/**************************************************************************/
void I2CSensor::I2CWrite(uint8_t addr) {
#if ARDUINO >= 100
  Wire.write((uint8_t)addr);
#else
  Wire.send(addr);
#endif
}

uint8_t I2CSensor::ReadRegister(uint8_t reg) {
  Wire.beginTransmission(addr);
  I2CWrite(reg);
  Wire.endTransmission();
  Wire.requestFrom(addr, 1);
  return (I2CRead());
}

uint8_t* I2CSensor::ReadRegister(uint8_t reg, uint8_t read_size){
  uint8_t *data = new uint8_t[read_size];
  
  Wire.beginTransmission(addr);
  I2CWrite(reg);
  Wire.endTransmission();
  //delay(500);

  Wire.requestFrom((uint8_t)addr, (uint8_t)read_size);

  if (Wire.available() == read_size)
  {
    for (int i=0; i < read_size; i++)
    data[i] = Wire.read();
  }

  return data;
}

void I2CSensor::WriteRegister(uint8_t reg, uint8_t value) {
  Wire.beginTransmission(addr);
  I2CWrite((uint8_t)reg);
  I2CWrite((uint8_t)(value));
  Wire.endTransmission();
}

void I2CSensor::WriteRegBit(uint8_t reg, uint8_t xbit, State st) {
  uint8_t tmp = ReadRegister(reg);

  if (st)
    WriteRegister(reg, tmp | xbit);
  else
    WriteRegister(reg, tmp & ~xbit);
}

