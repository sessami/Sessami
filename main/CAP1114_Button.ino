/**************************************************************************************
  Title : Sessami CAP1114 Button class
  Created by : Kaz Wong
  Date : 7 Dec 2016
  Description : class for handle button state
 ***************************************************************************************/

#include "CAP1114_Button.h"

using namespace CAP1114;

bool Sessami_Button::operator==(const ButtonEnum button) const {
  if ((button_state & (uint8_t)button) > 0)
    return true;
  return false;
}

bool Sessami_Button::operator==(const SlideEnum slide) const {
  if ((slide_state & (uint8_t)slide) > 0)
    return true;
  return false;
}

bool Sessami_Button::operator==(const unsigned int key) const {
  if (key < 256) {
    if ( (((unsigned int)button_state & key) > 0) && (button_tap == 1) )
      return true;
    else if ( (((unsigned int)button_state & key) > 0) && (button_tap > 1) && (button_hold_t > 2) )
      return true;
  } else {
    if ( (unsigned int)slide_state & ( key - 256 ) > 0)
      return true;
  }

  return false;
}

void Sessami_Button::UpdateBut() {
  uint16_t cs = 0;
  uint8_t ss = 0, ssB01 = 0, ssB56 = 0, ssB23 = 0;

  UpdateSlide();
  ss = GetSlide();

  UpdateCS();
  cs = GetCS();

  button_state = (uint8_t)(cs & B00111111);
  button_state |= (uint8_t)((cs >> 2) & B01000000);

  if (ss > 0) {
    Serial.print("ss ");
    Serial.println(ss, 2);
  }

  ssB01 = (ss & B00000011);
  ssB23 = ( (uint8_t)(cs & B11000000) ) >> 4;
  ssB56 = (ss & B01100000);
  slide_state = ssB01 + ssB23 + ssB56;

  if (slide_state > 0) {
    Serial.print("slide_state ");
    Serial.println(slide_state, 2);
  }

  if (button_state > 1)
    button_tap++;
  else
    button_tap = 0;

  if ((button_state != 0) || (slide_state != 0))
    held_t = 0;
  if (button_state < 2)
    button_hold_t = 0;
}

uint8_t Sessami_Button::GetBut() {
  return button_state;
}

uint8_t Sessami_Button::GetSli() {
  return slide_state;
}

unsigned long Sessami_Button::GetHeldT() {
  return held_t;
}

void Sessami_Button::HeldCount() {
  held_t++;
}

void Sessami_Button::HoldCount() {
  button_hold_t++;
}

bool Sessami_Button::BuTap() {
  if (button_tap == 1)
    return true;
  else
    return false;
}

void Sessami_Button::SetPROXSen(uint8_t value) {
  prox_sen = value;
  SetProxSen(value);
}

uint8_t Sessami_Button::GetPROXSen() {
  return prox_sen;
}

void Sessami_Button::SetButSen(uint8_t value) {
  delta_sen = value;
  SetDeltaSen(value);
}

uint8_t Sessami_Button::GetButSen() {
  return delta_sen;
}

//TODO
int8_t Sessami_Button::GetDeltaCount(uint8_t key) {
  switch (key) {
    case B_PROX :
      return delta_count[0] = GetSDelta(SDelta_CS1);
      break;
    case B_UP :
      return delta_count[1] = GetSDelta(SDelta_CS2);
      break;
    case B_DOWN :
      return delta_count[2] = GetSDelta(SDelta_CS3);
      break;
    case B_POWER :
      return delta_count[3] = GetSDelta(SDelta_CS4);
      break;
    case B_RIGHT :
      return delta_count[4] = GetSDelta(SDelta_CS5);
      break;
    case B_MID :
      return delta_count[5] = GetSDelta(SDelta_CS6);
      break;
    case B_LEFT :
      return delta_count[6] = GetSDelta(SDelta_CS7);
      break;
  }
}

//TODO
uint8_t Sessami_Button::GetTh(uint8_t key) {
  switch (key) {
    case B_PROX :
      return threshold[0] = GetThresh(Thresh_CS1);
      break;
    case B_UP :
      return threshold[1] = GetThresh(Thresh_CS2);
      break;
    case B_DOWN :
      return threshold[2] = GetThresh(Thresh_CS3);
      break;
    case B_POWER :
      return threshold[3] = GetThresh(Thresh_CS4);
      break;
    case B_RIGHT :
      return threshold[4] = GetThresh(Thresh_CS5);
      break;
    case B_MID :
      return threshold[5] = GetThresh(Thresh_CS6);
      break;
    case B_LEFT :
      return threshold[6] = GetThresh(Thresh_CS7);
      break;
  }
}

//TODO
uint8_t Sessami_Button::SetTh(uint8_t key, uint8_t value) {
  switch (key) {
    case B_PROX :
      SetThresh(Thresh_CS1, value);
      threshold[0] = value;
      break;
    case B_UP :
      SetThresh(Thresh_CS2, value);
      threshold[1] = value;
      break;
    case B_DOWN :
      SetThresh(Thresh_CS3, value);
      threshold[2] = value;
      break;
    case B_POWER :
      SetThresh(Thresh_CS4, value);
      threshold[3] = value;
      break;
    case B_RIGHT :
      SetThresh(Thresh_CS5, value);
      threshold[4] = value;
      break;
    case B_MID :
      SetThresh(Thresh_CS6, value);
      threshold[5] = value;
      break;
    case B_LEFT :
      SetThresh(Thresh_CS7, value);
      threshold[6] = value;
      break;
  }
}

uint8_t Sessami_Button::Getthreshold(uint8_t key) {
  switch (key) {
    case B_PROX :
      return threshold[0];
      break;
    case B_UP :
      return threshold[1];
      break;
    case B_DOWN :
      return threshold[2];
      break;
    case B_POWER :
      return threshold[3];
      break;
    case B_RIGHT :
      return threshold[4];
      break;
    case B_MID :
      return threshold[5];
      break;
    case B_LEFT :
      return threshold[6];
      break;
  }
}
