#ifdef __IN_ECLIPSE__
//This is a automatic generated file
//Please do not modify this file
//If you touch this file your change will be overwritten during the next build
//This file has been generated on 2016-11-16 16:23:59

#include "Arduino.h"
#include "CAP1114_Driver.h"
#include "CAP1114_TouchController.h"
#include "I2CSensor.h"
#include "ImageDraw_ESP8266.h"
#include "OpenWeather_ESP8266.h"
#include <String>
#include "SessamiButton.h"
#include "SessamiController.h"
#include "SessamiUI.h"
#include <Arduino.h>
#include "SessamiController.h"
#include "TemperatureHumidity_Si7006A20.h"
#include "Time_ESP8266.h"
#include <TimeLib.h>
#include "WifiManage.h"
void TouchController::Toggle() ;
uint8_t I2CSensor::I2CRead() ;
void I2CSensor::I2CWrite(uint8_t addr) ;
uint8_t I2CSensor::ReadRegister(uint8_t reg) ;
uint8_t* I2CSensor::ReadRegister(uint8_t reg, uint8_t read_size);
void I2CSensor::WriteRegister(uint8_t reg, uint8_t value) ;
void I2CSensor::WriteRegBit(uint8_t reg, uint8_t xbit, State st) ;
void ImageDraw_ESP8266::ClearLCD() ;
void ImageDraw_ESP8266::initLCD() ;
void ImageDraw_ESP8266::bmpDraw(char *filename, uint8_t x, uint16_t y) ;
uint16_t ImageDraw_ESP8266::read16(File &f) ;
uint32_t ImageDraw_ESP8266::read32(File &f) ;
char* OpenWeather_ESP8266::viewWeatherFeeds(char* unit,int* queryLength) ;
char* OpenWeather_ESP8266::viewWeatherFeeds(char* apiReadKey, char* parameter,char* unit,int* queryLength) ;
char* OpenWeather_ESP8266::viewWeatherFeeds(char* apiReadKey, char* parameter1,char* parameter2,char* unit,int* queryLength) ;
void OpenWeather_ESP8266::getRequestResponse(char* getresource) ;
void OpenWeather_ESP8266::parseUserData(char* content)   ;
char* OpenWeather_ESP8266::getWeatherIcon() ;
void OpenWeather_ESP8266::wait()  ;
bool OpenWeather_ESP8266::getRequest(char* host,char* resource)  ;
void OpenWeather_ESP8266::readResponseContent(char* content, size_t maxSize)  ;
bool OpenWeather_ESP8266::skipResponseHeaders()  ;
bool OpenWeather_ESP8266::connect( char* hostName)  ;
void OpenWeather_ESP8266::disconnect()  ;
void Button::UpdateBut() ;
uint8_t Button::GetBut() ;
uint8_t Button::GetSli() ;
void SessamiController::Background() ;
void SessamiController::StateMachine() ;
void UI_ESP8266::initScr() ;
void UI_ESP8266::Main() ;
void UI_ESP8266::UIStateMachine(bool rst) ;
void UI_ESP8266::Keyboard() ;
char* UI_ESP8266::Input() ;
void Toggle() ;
void setup() ;
void loop() ;
bool TemperatureHumidity_Si7006A20::initWireI2C() ;
void TemperatureHumidity_Si7006A20::UpdateTemperatureHumidity() ;
void Time_ESP8266::initTime() ;
time_t Time_ESP8266::getNtpTime() ;
void Time_ESP8266::sendNTPpacket(IPAddress &address) ;
bool WifiManage::initWiFiConnection() ;

#include "Smart_Controller.ino"

#include "CAP1114_Driver_v1.0.ino"
#include "CAP1114_TouchController.ino"
#include "I2CSensor_v1.0.ino"
#include "ImageDraw_ESP8266_v1.0.ino"
#include "OpenWeather_ESP8266v1.0.ino"
#include "SessamiButon.ino"
#include "SessamiController.ino"
#include "SessamiUI.ino"
#include "TemperatureHumidity_Si7006A20_v1.0.ino"
#include "Time_ESP8266_v1.0.ino"
#include "WifiManage_v1.0.ino"

#endif
