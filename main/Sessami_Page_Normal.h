/**************************************************************************************
  Title : Sessami UI Page class
  Created by : Kaz Wong
  Date : 7 Dec 2016
  Description : Class of Sessami UI page
 ***************************************************************************************/

#include "SessamiUI.h"
#include "Thermostat.h"
#include <OpenWeather_ESP8266.h>

class Page_Normal : private SessamiUI {
  private:
    OpenWeather_ESP8266 openweather;

    unsigned long loop_t;
    unsigned long last_t;
    int sub_state;
    bool show_sub;
    Coordinates co[6];

    void Main();
    void Sub();

    uint8_t LoopTime(unsigned int color);
    uint8_t PageTitle(unsigned int color);
    uint8_t Date(unsigned int color);
    uint8_t Time(unsigned int color);
    uint8_t C0(unsigned int color);
    uint8_t C1(unsigned int color);
    uint8_t C2(unsigned int color);
    uint8_t C3(unsigned int color);

  public:
    virtual uint8_t EvMin();
    virtual uint8_t EvHr();
    virtual uint8_t UIStateMachine(bool rst);

    Page_Normal();
    virtual ~Page_Normal();
};

Page_Normal::Page_Normal() :  sub_state(0), show_sub(true), loop_t(0), last_t(0) {
  co[0].x = 160; co[0].y = 140;
  co[1].x = 45; co[1].y = 140;
  co[2].x = 50; co[2].y = 55;
  co[3].x = 222; co[3].y = 165;
}

Page_Normal::~Page_Normal() {

}

uint8_t Page_Normal::EvMin() {
  Time(ILI9341_WHITE);
}

uint8_t Page_Normal::EvHr() {
  Date(ILI9341_WHITE);
}

uint8_t Page_Normal::UIStateMachine(bool rst) {
  if (rst) {
    //image_draw->ClearLCD();
    PageTitle(ILI9341_WHITE);
    Date(ILI9341_WHITE);
    Time(ILI9341_WHITE);
    C0(ILI9341_WHITE);
    C1(ILI9341_WHITE);
    //C2(ILI9341_WHITE);
    C3(ILI9341_WHITE);
    //state = 0;
  }
  LoopTime(ILI9341_WHITE);

  Main();
  if (show_sub)
    Sub();

  return 0;
}

void Page_Normal::Main() {
  switch (state) {
    case 0 :
      break;
    case 1 :
      break;
    case 2 :
      break;
  }
}

void Page_Normal::Sub() {
  switch (sub_state) {
    case 0 :
      break;
    case 1 :
      break;
    case 2 :
      break;
  }

  if (*button == B_MID) {
    state = sub_state;
  }
}

uint8_t Page_Normal::PageTitle(unsigned int color) {
  tft.fillRect(235, 0, 100, 13, ILI9341_BLACK);
  tft.setTextColor(color);

  tft.setFont(&LiberationSans_Regular6pt7b);
  tft.setCursor(250, 10);
  tft.print("Main");

  return 0;
}

uint8_t Page_Normal::LoopTime(unsigned int color) {
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

uint8_t Page_Normal::Time(unsigned int color) {
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

uint8_t Page_Normal::Date(unsigned int color) {
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

/****************************************************************
                                 Standby Screen
*/
uint8_t Page_Normal::C0(unsigned int color) {
  tft.setTextColor(color);

  tft.setCursor(co[0].x, co[0].y);
  tft.setFont(&LiberationSans_Regular28pt7b);
  tft.print("25.5");
  tft.setFont(&LiberationSans_Regular4pt7b);
  tft.print(" o");

  return 0;
}

uint8_t Page_Normal::C1(unsigned int color) {
  tft.setTextColor(color);

  tft.setCursor(co[1].x, co[1].y);
  tft.setFont(&LiberationSans_Regular18pt7b);
  tft.print(openweather.GetTemp(), 1);
  tft.setFont(&LiberationSans_Regular4pt7b);
  tft.print(" o");

  return 0;
}

uint8_t Page_Normal::C2(unsigned int color) {
  tft.setTextColor(color);

  image_draw->bmpDraw(openweather.getWeatherIcon(), co[2].x, co[2].y);

  return 0;
}

uint8_t Page_Normal::C3(unsigned int color) {
  tft.setTextColor(color);

  tft.setCursor(co[3].x, co[3].y);
  tft.setFont(&LiberationSans_Regular12pt7b);
  tft.print("25.5");
  tft.setFont(&LiberationSans_Regular4pt7b);
  tft.print(" o");

  return 0;
}
