/**************************************************************************************
  Title : Sessami UI Page class
  Created by : Kaz Wong
  Date : 7 Dec 2016
  Description : Class of Sessami UI page
 ***************************************************************************************/

#include "SessamiUI.h"
#include <OpenWeather_ESP8266.h>
#include "Thermostat.h"

extern tmElements_t _time;

class Page_Standby : private SessamiUI {
  private:
    unsigned long loop_t;
    unsigned long last_t;
    OpenWeather_ESP8266 openweather;
    Coordinates co[6];

    uint8_t PageTitle(unsigned int color);
    uint8_t LoopTime(unsigned int color);
    uint8_t Time(unsigned int color);
    uint8_t Date(unsigned int color);
    uint8_t C0(unsigned int color);
    uint8_t C1(unsigned int color);
    uint8_t C2(unsigned int color);
    uint8_t C3(unsigned int color);
    
    
  public:
    virtual uint8_t EvMin();
    virtual uint8_t EvHr();
    virtual uint8_t UIStateMachine(bool rst);

    Page_Standby();
    virtual ~Page_Standby();
};

Page_Standby::Page_Standby() {
  co[0].x = 160; co[0].y = 170;
  co[1].x = 45; co[1].y = 170;
  co[2].x = 50; co[2].y = 85;
  co[3].x = 222; co[3].y = 195;
}

Page_Standby::~Page_Standby() {

}

uint8_t Page_Standby::EvMin() {
  Time(ILI9341_WHITE);
}

uint8_t Page_Standby::EvHr() {
  Date(ILI9341_WHITE);
}

uint8_t Page_Standby::UIStateMachine(bool rst) {
  if (rst) {
    //image_draw->ClearLCD();
    PageTitle(ILI9341_WHITE);
    Date(ILI9341_WHITE);
    Time(ILI9341_WHITE);
    C0(ILI9341_WHITE);
    C1(ILI9341_WHITE);
    //C2(ILI9341_WHITE);
    C3(ILI9341_WHITE);
    
    state = 0;
  }
  LoopTime(ILI9341_WHITE);
  return 0;
}

uint8_t Page_Standby::PageTitle(unsigned int color) {
  tft.fillRect(235, 0, 100, 13, ILI9341_BLACK);
  tft.setTextColor(color);

  tft.setFont(&LiberationSans_Regular6pt7b);
  tft.setCursor(235, 10);
  tft.print("Standby");

  return 0;
}

uint8_t Page_Standby::LoopTime(unsigned int color) {
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

uint8_t Page_Standby::Time(unsigned int color) {
  tft.fillRect(140, 0, 52, 22, ILI9341_BLACK);
  tft.setTextColor(color);
  tft.setFont(&LiberationSans_Regular10pt7b);
  tft.setCursor(130, 15);
  if (_time.Hour > 9)
    tft.print(_time.Hour);
  else {
    tft.print("0");
    tft.print(_time.Hour);
  }
  tft.print(":");
  if (_time.Minute > 9)
    tft.print(_time.Minute);
  else {
    tft.print("0");
    tft.print(_time.Minute);
  }

  return 0;
}

uint8_t Page_Standby::Date(unsigned int color) {
  tft.fillRect(15, 0, 105, 22, ILI9341_BLACK);
  tft.setTextColor(color);
  tft.setFont(&LiberationSans_Regular10pt7b);
  tft.setCursor(15, 15);
  tft.print(day());
  tft.print(" ");
  tft.print(month());
  tft.print(" ");
  tft.print(year());

  return 0;
}

uint8_t Page_Standby::C0(unsigned int color) {
  tft.setTextColor(color);

  tft.setCursor(co[0].x, co[0].y);
  tft.setFont(&LiberationSans_Regular28pt7b);
  tft.print("25.5");
  tft.setFont(&LiberationSans_Regular4pt7b);
  tft.print(" o");

  return 0;
}

uint8_t Page_Standby::C1(unsigned int color) {
  tft.setTextColor(color);
  
  tft.setCursor(co[1].x, co[1].y);
  tft.setFont(&LiberationSans_Regular18pt7b);
  tft.print(openweather.GetTemp(), 1);
  tft.setFont(&LiberationSans_Regular4pt7b);
  tft.print(" o");

  return 0;
}

uint8_t Page_Standby::C2(unsigned int color) {
  tft.setTextColor(color);

  image_draw->bmpDraw(openweather.getWeatherIcon(), co[2].x, co[2].y);
  
  return 0;
}

uint8_t Page_Standby::C3(unsigned int color) {
  tft.setTextColor(color);

  tft.setCursor(co[3].x, co[3].y);
  tft.setFont(&LiberationSans_Regular12pt7b);
  tft.print("25.5");
  tft.setFont(&LiberationSans_Regular4pt7b);
  tft.print(" o");

  return 0;
}
