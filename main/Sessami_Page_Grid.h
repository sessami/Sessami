/**************************************************************************************
  Title : Sessami UI Page class
  Created by : Kaz Wong
  Date : 7 Dec 2016
  Description : Class of Sessami UI page to display grid
 ***************************************************************************************/

#include "SessamiUI.h"

class Page_Grid : private SessamiUI {
  public:
    virtual uint8_t UIStateMachine(bool rst);
    uint8_t C0(unsigned int color);

    Page_Grid();
    virtual ~Page_Grid();
};

Page_Grid::Page_Grid() {
}

Page_Grid::~Page_Grid() {

}

uint8_t Page_Grid::UIStateMachine(bool rst) {
  if (rst)
    C0(ILI9341_WHITE);
  return 0;
}

//Draw grid
uint8_t Page_Grid::C0(unsigned int color) {
  for (int i=0; i<240; i+=10) {
    tft.drawFastHLine(0, i, 320, color); //Horizontal
  }
  
  for (int i=0; i<320; i+=10) {
    tft.drawFastVLine(i, 0, 240, color); //Vertical
  }

   tft.drawFastHLine(0, 120, 320,  ILI9341_RED); //Horizontal mid
   tft.drawFastVLine(160, 0, 240,  ILI9341_RED); //Vertical mid
}
