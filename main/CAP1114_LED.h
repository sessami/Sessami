/**************************************************************************************
  Title : Sessami CAP1114 Button class
  Created by : Kaz Wong
  Date : 7 Dec 2016
  Description : class for handle button state
 ***************************************************************************************/

#ifndef SESSAMI_LED_H_
#define SESSAMI_LED_H_

#include "CAP1114_Driver.h"

using namespace CAP1114;

#define LED_SLIDE    B00000001
#define LED_UP        B00000010
#define LED_DOWN  B00000100
#define LED_SR        B00000001//LED9
#define LED_SL        B00000010//LED10
#define LED_PWR     B00001000
#define LED_PWR2    B00000100//LED11

class Sessami_LED: private CAP1114_Driver {
  public:
    Sessami_LED();
    ~Sessami_LED();

    void SetDutyCycle(uint8_t mx, uint8_t mn);
};

Sessami_LED::Sessami_LED() :
  CAP1114_Driver() {
}

Sessami_LED::~Sessami_LED() {

}

#endif
