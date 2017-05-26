/**************************************************************************************
  Title : Sessami UI Page class
  Created by : Kaz Wong
  Date : 7 Dec 2016
  Description : Class of Sessami UI page
 ***************************************************************************************/

#include "SessamiUI.h"

class Page_HelloWorld : private SessamiUI {
  public:
    virtual uint8_t UIStateMachine(bool rst);
    uint8_t C0(unsigned int color);
    uint8_t C1(unsigned int color);
    uint8_t C2(unsigned int color);

    Page_HelloWorld();
    virtual ~Page_HelloWorld();
};

Page_HelloWorld::Page_HelloWorld() {
}

Page_HelloWorld::~Page_HelloWorld() {

}

uint8_t Page_HelloWorld::UIStateMachine(bool rst) {
  if (rst) {
    //image_draw->ClearLCD();
    C0(ILI9341_WHITE);
    state = 0;
  }
  switch (state) {
    case 0 :
      if (*button == ButtonEnum::DOWN) {
        image_draw->ClearLCD();
        C0(ILI9341_BLACK);
        C1(ILI9341_WHITE);
        state = 1;
      }
      break;
    case 1 :
      if (*button == ButtonEnum::DOWN) {
        C0(ILI9341_WHITE);
        C2(ILI9341_WHITE);
        state = 2;
      }
      break;
    case 2 :
      if (*button == ButtonEnum::DOWN) {
        C1(ILI9341_BLACK);
        C0(ILI9341_WHITE);
        state = 0;
      }
      break;
  }

  return 0;
}

uint8_t Page_HelloWorld::C1(unsigned int color) {
  //Bounder
  tft.drawLine(0, 0, 319, 0, color); //Horizontal partition
  tft.drawLine(0, 239, 319, 239, color); //Horizontal partition
  tft.drawLine(0, 0, 0, 239, color); //Vertical partition
  tft.drawLine(319, 0, 319, 239, color); //Vertical partition

  //Cross
  tft.drawLine(0, 0, 319, 239, color);
  tft.drawLine(319, 0, 0, 239, color);

  tft.setTextColor(color);

  tft.setFont(&LiberationSans_Regular48pt7b);
  tft.setCursor(45, 100);
  tft.print("Hello");

  tft.setCursor(35, 200);
  tft.print("World");

  return 0;
}

//Draw grid
uint8_t Page_HelloWorld::C0(unsigned int color) {
  for (int i=0; i<240; i+=10) {
    tft.drawFastHLine(0, i, 320, color); //Horizontal
  }
  
  for (int i=0; i<320; i+=10) {
    tft.drawFastVLine(i, 0, 240, color); //Vertical
  }

   tft.drawFastHLine(0, 120, 320,  ILI9341_RED); //Horizontal mid
   tft.drawFastVLine(160, 0, 240,  ILI9341_RED); //Vertical mid
}

uint8_t Page_HelloWorld::C2(unsigned int color) {
  tft.setTextColor(color);

  tft.setFont(&LiberationSans_Regular48pt7b);
  tft.setCursor(20, 70);
  tft.print("abc48");

  tft.setFont(&LiberationSans_Regular40pt7b);
  tft.setCursor(20, 130);
  tft.print("abc40");
  
  tft.setFont(&LiberationSans_Regular28pt7b);
  tft.setCursor(20, 180);
  tft.print("abc28");
  
  tft.setFont(&LiberationSans_Regular20pt7b);
  tft.setCursor(20, 210);
  tft.print("abc20");
  
  tft.setFont(&LiberationSans_Regular16pt7b);
  tft.setCursor(20, 240);
  tft.print("abc16");
}

