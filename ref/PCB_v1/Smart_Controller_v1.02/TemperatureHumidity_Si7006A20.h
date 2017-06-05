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
#ifndef TEMPERATUREHUMIDITY_SI7006A20_H_
#define TEMPERATUREHUMIDITY_SI7006A20_H_

#include "I2CSensor.h"

class TemperatureHumidity_Si7006A20 : private I2CSensor {
  public:
    enum TempUnit {
      CELSIUS, FAHRENHEIT
    };

  private:
    float humidity;
    float temperature_celsius;
    float temperature_fahrenheit;

  public:
    TemperatureHumidity_Si7006A20();
    ~TemperatureHumidity_Si7006A20();

    virtual bool initWireI2C();
    void UpdateTemperatureHumidity();
    float GetHumidity() {
      return humidity;
    }
    float GetTemp(TempUnit u) {
      if (u)
        return temperature_fahrenheit;
      else
        return temperature_celsius;
    }
};

TemperatureHumidity_Si7006A20::TemperatureHumidity_Si7006A20() : I2CSensor(0x40),
  humidity(0), temperature_celsius(0), temperature_fahrenheit(32)
{
}

TemperatureHumidity_Si7006A20::~TemperatureHumidity_Si7006A20()
{
}

#endif
