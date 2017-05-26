/**************************************************************************************
  Title : Sessami CAP1114 controller class
  Created by : Kaz Wong
  Date : 7 Dec 2016
  Description : class for contorl CAP1114
 ***************************************************************************************/

#include "CAP1114_TouchController.h"

void TouchController::Toggle() {
}

void TouchController::Update() {
  UpdateMSControl();
  if (GetMSControl(MSControl::INT))
    SetMSControl(MSControl::INT, LO);
}
