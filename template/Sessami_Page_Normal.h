/**************************************************************************************
  Title : Sessami UI Page class
  Created by : Kaz Wong
  Date : 7 Dec 2016
  Description : Class of Sessami UI page
 ***************************************************************************************/

#include "SessamiUI.h"
#include "Thermostat.h"
#include <OpenWeather_ESP8266.h>

#define MAXIDX  3

class Page_Normal : private SessamiUI {
  private:
    OpenWeather_ESP8266 openweather;

    unsigned long loop_t;
    unsigned long last_t;
    int sub_state;
    string menu[MAXIDX];
    bool show_sub;
    Thermostat thermostat;
    int idx;
    bool set[3];
    bool prt;

    void Main();
    void Sub();

    void AirCon(bool prt);
    void Forecast(bool prt);
    void Setting(bool prt);

    uint8_t PageTitle(unsigned int color);
    uint8_t C1(unsigned int color);
    uint8_t C2(unsigned int color);
    uint8_t C3(unsigned int color);
    uint8_t C4(unsigned int i);
    uint8_t C5(unsigned int color);
    uint8_t LoopTime(unsigned int color);
  public:
    virtual uint8_t UIStateMachine(bool rst);

    Page_Normal();
    virtual ~Page_Normal();
};

Page_Normal::Page_Normal() :  sub_state(0), show_sub(true), idx(0), prt(true), loop_t(0), last_t(0), 
  menu( {
  "Air Con", "Forecast", "Setting"
}) {
  set[0] = false;
  set[1] = true;
  set[2] = false;
}

Page_Normal::~Page_Normal() {

}

uint8_t Page_Normal::UIStateMachine(bool rst) {
  if (rst) {
    image_draw->ClearLCD();
    PageTitle(ILI9341_WHITE);
    C1(ILI9341_WHITE);
    C2(ILI9341_WHITE);
    prt = true;
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
      AirCon(prt);
      break;
    case 1 :
      Forecast(prt);
      break;
    case 2 :
      Setting(prt);
      break;
  }
  prt = false;
}

void Page_Normal::Sub() {
  switch (sub_state) {
    case 0 :
      if (*button == B_LEFT)  {
        C1(ILI9341_BLACK);
        sub_state = 2;
        C1(ILI9341_WHITE);
      } else if (*button == B_RIGHT) {
        C1(ILI9341_BLACK);
        sub_state = 1;
        C1(ILI9341_WHITE);
      }
      break;
    case 1 :
      if (*button == B_LEFT) {
        C1(ILI9341_BLACK);
        sub_state = 0;
        C1(ILI9341_WHITE);
      } else if (*button == B_RIGHT) {
        C1(ILI9341_BLACK);
        sub_state = 2;
        C1(ILI9341_WHITE);
      }
      break;
    case 2 :
      if (*button == B_LEFT) {
        C1(ILI9341_BLACK);
        sub_state = 1;
        C1(ILI9341_WHITE);
      } else if (*button == B_RIGHT) {
        C1(ILI9341_BLACK);
        sub_state = 0;
        C1(ILI9341_WHITE);
      }
      break;
  }

  if (*button == B_MID) {
    state = sub_state;
    tft.fillRect(0, 15, 320, 195, ILI9341_BLACK);
    prt = true;
  }
}

uint8_t Page_Normal::PageTitle(unsigned int color) {
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

uint8_t Page_Normal::C1(unsigned int color) {
  tft.fillRect(0, 210, 320, 26, ILI9341_BLACK);

  tft.setTextColor(color);
  tft.setFont(&LiberationSans_Regular10pt7b);

  tft.setCursor(130, 225);
  tft.print(menu[sub_state]);

  return 0;
}

uint8_t Page_Normal::C2(unsigned int color) {
  tft.fillRect(20, 236, 60, 4, ILI9341_WHITE);
  tft.fillRect(130, 236, 60, 4, ILI9341_WHITE);
  tft.fillRect(240, 236, 60, 4, ILI9341_WHITE);
}

uint8_t Page_Normal::C3(unsigned int color) {
  tft.setTextColor(color);
  tft.setFont(&LiberationSans_Regular16pt7b);

  tft.setCursor(10, 115);
  tft.print((string)thermostat.GetAModeS());
}

uint8_t Page_Normal::C4(unsigned int i) {
  tft.setFont(&LiberationSans_Regular16pt7b);

  if (idx == i) {
    tft.fillRect(10, 45 + i * 30, 310, 30, ILI9341_WHITE);
    tft.setTextColor(ILI9341_BLACK);
  } else {
    tft.fillRect(10, 45 + i * 30, 310, 30, ILI9341_BLACK);
    tft.setTextColor(ILI9341_WHITE);
  }

  switch (i) {
    case 0 :
      tft.setCursor(10, 70);
      tft.print("Setting 0");
      tft.setCursor(220, 70);
      if (set[i])
        tft.print("ON");
      else
        tft.print("OFF");
      break;
    case 1 :
      tft.setCursor(10, 100);
      tft.print("Setting 1");
      tft.setCursor(220, 100);
      if (set[i])
        tft.print("ON");
      else
        tft.print("OFF");
      break;
    case 2 :
      tft.setCursor(10, 130);
      tft.print("Setting 2");
      tft.setCursor(220, 130);
      if (set[i])
        tft.print("ON");
      else
        tft.print("OFF");
      break;
    case 3 :
      tft.setCursor(10, 160);
      tft.print("Prox Sen");
      tft.setCursor(220, 160);
      tft.print(button->GetPROXSen());
      break;
    case 4 :
      tft.setCursor(10, 190);
      tft.print("Delta Sen");
      tft.setCursor(220, 190);
      tft.print(button->GetButSen());
      break;
  }
}

uint8_t Page_Normal::C5(unsigned int color) {
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(&LiberationSans_Regular6pt7b);
  tft.setCursor(10, 30);
  tft.print("Setting");
}

void Page_Normal::AirCon(bool prt) {
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(&LiberationSans_Regular6pt7b);
  tft.setCursor(10, 30);
  tft.print("Theromstat");

  tft.setFont(&LiberationSans_Regular10pt7b);
  tft.setCursor(10, 55);
  tft.print("Indoor Temperature : 25.5");

  tft.setCursor(10, 80);
  tft.print("Outdoor Temperature : ");
  tft.print(openweather.GetTemp(), 1);

  if ( (*button == ButtonEnum::UP) && (button->BuTap()) ) {
    int idx;
    idx = thermostat.GetAMode();
    if (++idx > 6)
      idx = 0;
    thermostat.SetAMode(idx);
    tft.fillRect(10, 90, 205, 50, ILI9341_BLACK);
  } else if ( (*button == ButtonEnum::DOWN) && (button->BuTap()) ) {
    int idx;
    idx = thermostat.GetAMode();
    if (--idx < 0)
      idx = 6;
    thermostat.SetAMode(idx);
    tft.fillRect(10, 90, 205, 50, ILI9341_BLACK);
  }

  C3(ILI9341_WHITE);
}

void Page_Normal::Forecast(bool prt) {
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(&LiberationSans_Regular6pt7b);
  tft.setCursor(10, 30);
  tft.print("Forecast");

}

void Page_Normal::Setting(bool prt) {
  if (prt) {
    C5(ILI9341_WHITE);
    for (int i=0; i<5; i++)
      C4(i);
  }
  
  if (*button == B_UP)  {
    int tmp = idx;
    if (--idx < 0)
      idx = 4;
    C4(tmp);
    C4(idx);
  } else if (*button == B_DOWN) {
    int tmp = idx;
    if (++idx > 4)
      idx = 0;
    C4(tmp);
    C4(idx);
  }

  int value = 0;
  switch (idx) {
    case 0:
    case 1:
    case 2:
      if ( (*button == SlideEnum::LEFT) || (*button == SlideEnum::RIGHT) ) {//( (*button == S_LEFT) || (*button == S_RIGHT) ) {
        set[idx] = !set[idx];
        C4(idx);
      }
    break;
    case 3:
      value = button->GetPROXSen();
      if ( (*button == SlideEnum::LEFT) && (value > 0) ) {
        value--;
        C4(idx);
        button->SetPROXSen(value);
      } else if ( (*button == SlideEnum::RIGHT) && (value < 7) ) {
        value++;
        C4(idx);
        button->SetPROXSen(value);
      }
      break;
    case 4:
      value = button->GetButSen();
      if ( (*button == SlideEnum::LEFT) && (value > 0) ) {
        value--;
        C4(idx);
        button->SetButSen(value);
      } else if ( (*button == SlideEnum::RIGHT) && (value < 7) ) {
        value++;
        C4(idx);
        button->SetButSen(value);
      }
      break;
  }
}

