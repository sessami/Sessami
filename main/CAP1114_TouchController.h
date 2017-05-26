/**************************************************************************************
  Title : Sessami CAP1114 controller class
  Created by : Kaz Wong
  Date : 7 Dec 2016
  Description : class for contorl CAP1114
 ***************************************************************************************/

#ifndef CAP1114_TOUCHCONTROLLER_H_
#define CAP1114_TOUCHCONTROLLER_H_

#include <CAP1114_Driver.h>

using namespace CAP1114;

class TouchController: protected CAP1114_Driver {
  public:
    TouchController();
    ~TouchController();
    
    void Toggle();
    void Update();
};

TouchController::TouchController() :
  CAP1114_Driver() {
  bool sg, gp;
  uint8_t rpt_ph, m_press, max_dur, rpt_sl;

#if defined(ESP8266)
  Serial.println("SPI Max Speed");
#endif

  Serial.println("---------CAP1114 initialization Start-----------");

  if (!initWireI2C())
    Serial.println("CAP1114 communication fail!");
  else {
    //--------------------------------CAP1114 initialization -----------------------------
    SetMTConfig(0);
    SetIntEn(0xFF);//(uint8_t)IntEn::G); //interrupt Enable
    Serial.print("Interrupt Enable : ");
    Serial.println(GetIntEn(), 2);

    SetMaxDurCalConfig(LO, LO);
    SetRptRateConfig(LO, HI);
    Serial.print("Repeat Rate Enable : ");
    GetRptRateConfig(&sg, &gp);
    Serial.print(sg);
    Serial.print("   ");
    Serial.println(gp);

    GetGroupConfig(&rpt_ph, &m_press, &max_dur, &rpt_sl);
    Serial.print("Group Config : ");
    Serial.print(rpt_ph, 2);
    Serial.print("   ");
    Serial.print(m_press, 2);
    Serial.print("   ");
    Serial.print(max_dur, 2);
    Serial.print("   ");
    Serial.println(rpt_sl, 2);

    SetGPIODir(B01111111);
    Serial.print("GPIO Direction: ");
    Serial.println(GetGPIODir(), 2);

    SetOutputType(B01110000);

    SetLEDLinking((uint8_t)LEDLinking::Group | (uint8_t)LEDLinking::CS4 | (uint8_t)LEDLinking::CS3 | (uint8_t)LEDLinking::CS2);
    SetAccelEN(HI);
    SetProxEN(HI); //On Proximity
    
    SetProxSen(4); //Set Sensivity  0-most, 7-least
    SetCalAct(0xFF); //Calibrate all Sensor
    
    SetDeltaSen(4);
    Serial.print("Delta Sensitivity : ");
    Serial.println(GetDeltaSen());
    
    SetLED(B00000000); // - | LEFT | MID | RIGHT | POWER | DOWN | UP | PROX

   SetMSControl(MSControl::INT, LO);
    
    Serial.println("---------CAP1114 initialization End-----------");
    Serial.println();
  }
}

TouchController::~TouchController() {
}

#endif

