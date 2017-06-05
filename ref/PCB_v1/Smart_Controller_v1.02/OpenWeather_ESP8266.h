/**************************************************************************************
  Original Contributor Information
  Sample Arduino Json Web Client
  Downloads and parse http://jsonplaceholder.typicode.com/users/1
  Copyright Benoit Blanchon 2014-2016
  MIT License
  Arduino JSON library
  https://github.com/bblanchon/ArduinoJson
  If you like this project, please add a star!
***************************************************************************************/
/**************************************************************************************
  Title : OpenWeather + ESP8266 Secure WiFi Connection Code using SHA-1 Fingerprint key
  Modified by : Sagar Naikwadi
  Date : 5th Sep 2016
  Version : 0.3
  Description : Works well with openweather upload and download with JSON format
***************************************************************************************/
#ifndef OPENWEATHERESP8266_H_
#define OPENWEATHERESP8266_H_


#include <ArduinoJson.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
//#include <WiFiClientSecure.h>
#include <String.h>

//#include "WifiManage.h"

extern "C"
{
#include "user_interface.h"
}

class OpenWeather_ESP8266
{
  private:
    unsigned long HTTP_TIMEOUT; //HTTP request/response timeout
    size_t MAX_CONTENT_SIZE; //HTTP response maximum content size

    
  private:
    //Server Parameters
    WiFiClient client;
    char* server; //Server IP Domain
    char* fingerprint; //SHA-1 Fingerprint Key for the Server

    char* apiReadKey;

    String description, city, country, icon_name;
    float temp, temp_min, temp_max;
    int pressure, humidity;

  public:
    // Constructor and Destructor
    OpenWeather_ESP8266(char*, char*);
    ~OpenWeather_ESP8266();

    //member function
    bool getRequest(char*, char*);
    bool skipResponseHeaders();
    void readResponseContent(char*, size_t);
    bool connect( char*);
    void disconnect();

    void getRequestResponse(char*);
    void parseUserData(char*);
    void wait();
    char* viewWeatherFeeds(char*, int*); //byName
    //char* viewWeatherFeeds(char*, char*, char*, int*); //byZipCode
    char* viewWeatherFeeds(char*, char*, char*, int*); //byCityID
    char* viewWeatherFeeds(char*, char*, char*, char*, int*); //byLatLong
    char* getWeatherIcon();

    String GetDescription() const {
      return description;
    }
    float GetTemp() const {
      return temp;
    }
    float GetMaxTemp() const {
      return temp_max;
    }
    float GetMinTemp() const {
      return temp_min;
    }
    int GetPressure() const {
      return pressure;
    }
    int GetHumidity() const {
      return humidity;
    }
};

OpenWeather_ESP8266::OpenWeather_ESP8266(char* apiReadKey, char* city) : apiReadKey(apiReadKey), city(city)
{
  //Default constructor -  Modify as per user requires it
  //Website and Wi-Fi Connection parameters
  server = "api.openweathermap.org";
  fingerprint = "AA 3B D4 93 7C E6 91 A5 61 89 75 F2 CB C8 BA B0 42 B3 0C 74";

  temp = 0;
  temp_min = 0;
  temp_max = 0;
  humidity = 0;
  pressure = 0;
  icon_name = "";

  HTTP_TIMEOUT = 10000;
  MAX_CONTENT_SIZE = 2048;
}

OpenWeather_ESP8266::~OpenWeather_ESP8266()
{
  //Default Destructor - Blank
}
#endif
