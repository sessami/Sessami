/**************************************************************************************
  Title : Sessami UI Page class
  Created by : Kaz Wong
  Date : 7 Dec 2016
  Description : Class of Sessami UI page
 ***************************************************************************************/
 
#include "SessamiUI.h"
#include "SessamiController.h"
#include <OpenWeather_ESP8266.h>

extern tmElements_t _time;

class Page_SmartThermostat : private SessamiUI {
  private:
    unsigned long loop_t;
    unsigned long last_t;
    OpenWeather_ESP8266 openweather;
    uint8_t anime_state;
    uint8_t anime_t;
    bool updown;

  public:
    virtual uint8_t UIStateMachine(bool rst);
    uint8_t Main(bool);
    uint8_t End(bool);
    uint8_t OutdoorWeather(bool);
    uint8_t TimeNow(bool);

    uint8_t PageTitle(unsigned int color);
    uint8_t LoopTime(unsigned int color);
    void C0(unsigned int color);
    void C1(unsigned int color);
    void C2(unsigned int color);
    void C3(unsigned int color);
    void C4(unsigned int color);
    void C5(unsigned int color);

    void C6(unsigned int color);
    void C7(unsigned int color);
    void C8(unsigned int color);
    void C9(unsigned int color);
    void C10(unsigned int color);
    void C11(unsigned int color);

    Page_SmartThermostat();
    virtual ~Page_SmartThermostat();
};

Page_SmartThermostat::Page_SmartThermostat() : anime_state(0), anime_t(0), updown(true) {
}

Page_SmartThermostat::~Page_SmartThermostat() {

}

uint8_t Page_SmartThermostat::UIStateMachine(bool rst) {
  if (rst)
    state = 0;
  PageTitle(ILI9341_WHITE);
  switch (state) {
    case 0 : Main(rst);
    case 1 : End(rst);
    case 2 : OutdoorWeather(rst);
    case 3 : state = TimeNow(rst);
  }
  
  LoopTime(ILI9341_WHITE);
  
  if (millis() - anime_t >= 50) {
    switch (anime_state) {
      case 0 : 
        C1(ILI9341_BLACK);
        C0(ILI9341_WHITE);
        break;
      case 1 : 
        C0(ILI9341_BLACK);
        C2(ILI9341_BLACK);
        C1(ILI9341_WHITE);
        break;
      case 2 : 
        C1(ILI9341_BLACK);
        C3(ILI9341_BLACK);
        C2(ILI9341_WHITE);
        break;
      case 3 : 
        C2(ILI9341_BLACK);
        C4(ILI9341_BLACK);
        C3(ILI9341_WHITE);
        break;
      case 4 : 
        C3(ILI9341_BLACK);
        C5(ILI9341_BLACK);
        C4(ILI9341_WHITE);
        break;
      case 5 : 
        C4(ILI9341_BLACK);
        C5(ILI9341_WHITE);
        break;
    }
    switch (anime_state) {
      case 0 : 
        C7(ILI9341_BLACK);
        C6(ILI9341_WHITE);
        break;
      case 1 : 
        C6(ILI9341_BLACK);
        C8(ILI9341_BLACK);
        C7(ILI9341_WHITE);
        break;
      case 2 : 
        C7(ILI9341_BLACK);
        C9(ILI9341_BLACK);
        C8(ILI9341_WHITE);
        break;
      case 3 : 
        C8(ILI9341_BLACK);
        C10(ILI9341_BLACK);
        C9(ILI9341_WHITE);
        break;
      case 4 : 
        C9(ILI9341_BLACK);
        C11(ILI9341_BLACK);
        C10(ILI9341_WHITE);
        break;
      case 5 : 
        C10(ILI9341_BLACK);
        C11(ILI9341_WHITE);
        break;
    }
    anime_t = millis();
    if (updown)
      anime_state++;
    else
      anime_state--;
      
    if (anime_state == 0)
      updown = true;
    else if (anime_state == 5)
      updown = false;
  }
  
  return 0;
}

uint8_t Page_SmartThermostat::PageTitle(unsigned int color) {
  tft.setTextColor(color);

  tft.setFont(&LiberationSans_Regular6pt7b);
  tft.setCursor(235, 10);
  tft.print("SagarPa");

  return 0;
}

uint8_t Page_SmartThermostat::LoopTime(unsigned int color) {
  tft.setFont(&LiberationSans_Regular6pt7b);
  
  tft.setCursor(285, 10);
  tft.setTextColor(ILI9341_BLACK);
  tft.print(loop_t);

  tft.setCursor(285, 10);
  tft.setTextColor(color);
  loop_t = millis() - last_t;
  tft.print(loop_t);
  last_t = millis();
}

void Page_SmartThermostat::C0(unsigned int color) {
  tft.setTextColor(color);
  tft.setCursor(250, 50);
  tft.print("Move");
}
void Page_SmartThermostat::C1(unsigned int color) {
  tft.setTextColor(color);
  tft.setCursor(250, 60);
  tft.print("Move");
}
void Page_SmartThermostat::C2(unsigned int color) {
  tft.setTextColor(color);
  tft.setCursor(250, 70);
  tft.print("Move");
}
void Page_SmartThermostat::C3(unsigned int color) {
  tft.setTextColor(color);
  tft.setCursor(250, 80);
  tft.print("Move");
}
void Page_SmartThermostat::C4(unsigned int color) {
  tft.setTextColor(color);
  tft.setCursor(250, 90);
  tft.print("Move");
}
void Page_SmartThermostat::C5(unsigned int color) {
  tft.setTextColor(color);
  tft.setCursor(250, 100);
  tft.print("Move");
}

//////////////////////////////////////////////////////////////////////////////

void Page_SmartThermostat::C6(unsigned int color) {
  tft.drawLine(20, 125, 145, 125, color); //Horizontal partition
  tft.drawLine(20, 126, 145, 126, color);
}
void Page_SmartThermostat::C7(unsigned int color) {
  tft.drawLine(40, 120, 80, 170, color); //Horizontal partition
  tft.drawLine(40, 121, 80, 170, color);
}
void Page_SmartThermostat::C8(unsigned int color) {
  tft.drawLine(60, 63, 190, 206, color); //Horizontal partition
  tft.drawLine(60, 64, 190, 207, color);
}
void Page_SmartThermostat::C9(unsigned int color) {
  tft.drawLine(65, 38, 250, 85, color); //Horizontal partition
  tft.drawLine(65, 39, 250, 86, color);
}
void Page_SmartThermostat::C10(unsigned int color) {
  tft.drawLine(120, 205, 310, 235, color); //Horizontal partition
  tft.drawLine(120, 206, 310, 236, color);
}
void Page_SmartThermostat::C11(unsigned int color) {
  tft.drawLine(12, 22, 95, 125, color); //Horizontal partition
  tft.drawLine(12, 23, 95, 126, color);
}

uint8_t Page_SmartThermostat::Main(bool rst) {
  image_draw->ClearLCD();
  tft.drawLine(80, 135, 80, 175, ILI9341_WHITE); //Vertical partition
  tft.drawLine(81, 135, 81, 175, ILI9341_WHITE);

  tft.drawLine(160, 30, 160, 185, ILI9341_WHITE); //Vertical partition
  tft.drawLine(161, 30, 161, 185, ILI9341_WHITE);
  
  return 1;
}

uint8_t Page_SmartThermostat::End(bool rst) {
  tft.drawLine(0, 24, 60, 24, ILI9341_WHITE);

  tft.drawLine(65, 23, 125, 23, ILI9341_WHITE);
  tft.drawLine(65, 24, 125, 24, ILI9341_WHITE);

  tft.drawLine(130, 23, 190, 23, ILI9341_WHITE);
  tft.drawLine(130, 24, 190, 24, ILI9341_WHITE);
  tft.drawLine(130, 25, 190, 25, ILI9341_WHITE);

  tft.drawLine(195, 23, 255, 23, ILI9341_WHITE);
  tft.drawLine(195, 24, 255, 24, ILI9341_WHITE);
  tft.drawLine(195, 25, 255, 25, ILI9341_WHITE);
  tft.drawLine(195, 26, 255, 26, ILI9341_WHITE);

  tft.drawLine(260, 22, 319, 22, ILI9341_WHITE);
  tft.drawLine(260, 23, 319, 23, ILI9341_WHITE);
  tft.drawLine(260, 24, 319, 24, ILI9341_WHITE);
  tft.drawLine(260, 25, 319, 25, ILI9341_WHITE);
  tft.drawLine(260, 26, 319, 26, ILI9341_WHITE);

  tft.fillRect(175, 180, 140, 40, ILI9341_BLACK);
  tft.drawRect(175, 180, 140, 40, ILI9341_WHITE); //Outline for Current humidity
  tft.setCursor(250, 200);
  tft.setFont(&LiberationSans_Regular10pt7b);
  tft.print("Cool");

  return 2;
}

uint8_t Page_SmartThermostat::OutdoorWeather(bool rst) {
  tft.setFont(&LiberationSans_Regular6pt7b);

  tft.fillRect(15, 30, 130, 90, ILI9341_BLACK);
  //           tft.drawRect(15,30,135,90,ILI9341_WHITE); //Outline for Outside weather
  tft.setCursor(105, 70);
  //           tft.print("Weather :");
  tft.println(openweather.GetDescription());


  tft.fillRect(15, 130, 60, 25, ILI9341_BLACK);
  //           tft.drawRect(15,130,60,25,ILI9341_WHITE); //Outline for Min temperature

  tft.setCursor(20, 110);
  tft.setFont(&LiberationSans_Regular14pt7b);
  //           tft.print("Current Temp :");
  tft.print(openweather.GetTemp(), 1);
  tft.setFont(&LiberationSans_Regular4pt7b);
  tft.print(" o");
  tft.setFont(&LiberationSans_Regular6pt7b);
  tft.print("C");

  tft.setCursor(105, 110);
  tft.setFont(&LiberationSans_Regular8pt7b);
  //           tft.print("Humidity :");
  tft.print(openweather.GetHumidity(), 1);
  tft.setFont(&LiberationSans_Regular4pt7b);
  tft.print(" %RH");

  tft.fillRect(85, 130, 60, 25, ILI9341_BLACK);

  tft.setCursor(25, 145);
  tft.setFont(&LiberationSans_Regular8pt7b);
  tft.print(openweather.GetMinTemp(), 0);
  tft.setFont(&LiberationSans_Regular4pt7b);
  tft.print(" o");
  tft.println("C");

  tft.setCursor(35, 165);
  tft.setFont(&LiberationSans_Regular6pt7b);
  tft.print("Min");

  tft.setCursor(95, 145);
  tft.setFont(&LiberationSans_Regular8pt7b);
  tft.print(openweather.GetMaxTemp(), 0);
  tft.setFont(&LiberationSans_Regular4pt7b);
  tft.print(" o");
  tft.println("C");


  tft.setCursor(105, 165);
  tft.setFont(&LiberationSans_Regular6pt7b);
  tft.print("Max");

  //imagedrawObj.bmpDraw(openweather.getWeatherIcon(), 25, 30);
  return 3;
}

uint8_t Page_SmartThermostat::TimeNow(bool rst) {
  
  tft.setFont(&LiberationSans_Regular10pt7b);
  tft.setCursor(15, 20);
  tft.print(_time.Hour);
  tft.print(":");
  tft.print(_time.Minute);

  tft.setCursor(110, 20);
  tft.setFont(&LiberationSans_Regular10pt7b);
  tft.print(day());
  tft.print(" ");
  tft.print(month());
  tft.print(" ");
  tft.print(year());

  return 3;
}


