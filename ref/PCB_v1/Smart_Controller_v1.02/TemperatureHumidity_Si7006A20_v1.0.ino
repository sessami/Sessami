/**************************************************************************************
  Original Contributor Information
  // Distributed with a free-will license.
  // Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
  // SI7006-A20
  // This code is designed to work with the SI7006-A20_I2CS I2C Mini Module available from ControlEverything.com.
  // https://www.controleverything.com/content/Humidity?sku=SI7006-A20_I2CS#tabs-0-product_tabset-2
***************************************************************************************/
/**************************************************************************************
  Title : ESP8266 + Si7006-A20 Communication
  Modified by : Sagar Naikwadi
  Date : 15th Sep 2016
  Version : 0.1
  Description : Communicates the Humidity and Temperature Information from Sensor to ESP8266
***************************************************************************************/
#include "TemperatureHumidity_Si7006A20.h"

bool TemperatureHumidity_Si7006A20::initWireI2C() {
  return true;
}

void TemperatureHumidity_Si7006A20::UpdateTemperatureHumidity()
{
  uint8_t *hum, *tem;
  
  hum = ReadRegister(0xF5, 2);

  humidity = ((hum[0] * 256.0) + hum[1]);
  humidity = ((125 * humidity) / 65536.0) - 6;


  tem = ReadRegister(0xF3, 2);

  float temp  = ((tem[0] * 256.0) + tem[1]);
  temperature_celsius = ((175.72 * temp) / 65536.0) - 46.85;
  temperature_fahrenheit =  temperature_celsius * 1.8 + 32;

  delete [] hum;
  delete [] tem;
}
