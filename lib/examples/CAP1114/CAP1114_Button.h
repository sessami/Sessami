/**************************************************************************************
  Title : Sessami CAP1114 Button class
  Created by : Kaz Wong
  Date : 7 Dec 2016
  Description : class for handle button state
 ***************************************************************************************/

#ifndef SESSAMI_BUTTON_H_
#define SESSAMI_BUTTON_H_

#include "CAP1114_Driver.h"

using namespace CAP1114;

#define B_PROX 1 //Sensor 1
#define B_MID 32 //Sensor 6
#define B_LEFT 64 //Sensor 7
#define B_UP 2 //Sensor 2
#define B_POWER 8 //Sensor 4
#define B_DOWN 4 //Sensor 3
#define B_RIGHT 16 //Sensor 5

//#define S_PH 257 //256 + 1  change to bool
//#define S_TAP 258 //256 + 2  change to bool
#define S_RIGHT 260 //256 +1
#define S_LEFT 264 //256 + 2
//#define S_RESET 288 //256+32
//#define S_MULT 320 //256+64

class Sessami_Button: private CAP1114_Driver {
  private:
    uint8_t button_state;
    uint8_t slide_state;
    unsigned long held_t;
    unsigned long button_hold_t;
    unsigned int button_tap;
    uint8_t slide_tap;
    uint8_t slide_ph;
    
    static uint8_t delta_sen;
    static uint8_t prox_sen;
    static uint8_t threshold[8];
    static int8_t delta_count[8];
  public:
    Sessami_Button();
    ~Sessami_Button();

    bool operator==(const unsigned int key) const;

    void UpdateBut();
    uint8_t GetBut();
    uint8_t GetSli();
    unsigned long GetHeldT();
    void HeldCount();
    void HoldCount();
    bool BuTap();

    //42h Prox Sensitivity
    void SetPROXSen(uint8_t value);
    uint8_t GetPROXSen();
    //1Fh Data Sensitivity
    void SetButSen(uint8_t value);
    uint8_t GetButSen();
    //10h-1Dh Delta Count
    int8_t GetDeltaCount(uint8_t key);
    //30h-37h Sensor Threshold
    uint8_t GetTh(uint8_t key);
    uint8_t SetTh(uint8_t key, uint8_t value);
    uint8_t Getthreshold(uint8_t key); //tmp
};

uint8_t Sessami_Button::button_state = 0;
uint8_t Sessami_Button::slide_state = 0;
unsigned long Sessami_Button::held_t = 0;
unsigned long Sessami_Button::button_hold_t = 0;
unsigned int Sessami_Button::button_tap = 0;
bool Sessami_Button::slide_tap = 0;
bool Sessami_Button::slide_ph = 0;
uint8_t Sessami_Button::delta_sen = 4; //0-most, 7-least
uint8_t Sessami_Button::prox_sen = 4; //0-most, 7-least
uint8_t Sessami_Button::threshold[8] = {0, 0, 0, 0,   0, 0, 0, 0};
int8_t Sessami_Button::delta_count[8] = {0, 0, 0, 0,   0, 0, 0, 0};

Sessami_Button::Sessami_Button() :
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
    //--------------------------------CAP1114 Test -----------------------------
    SetGPIODir(B01111111);
    Serial.print("GPIO Direction: ");
    Serial.println(GetGPIODir(), 2);

    SetOutputType(B01110000);
    
    SetMTConfig(0); //Multi Touch

    SetProxSen(4); //Set Sensivity  0-most, 7-least
    SetCalAct(0xFF); //Calibrate all Sensor
   /* SetDeltaSen(4);
    Serial.print("Delta Sensitivity : ");
    Serial.println(GetDeltaSen());*/

    
    /*SetIntEn(0xFF);//(uint8_t)IntEn::G); //interrupt Enable
    Serial.print("Interrupt Enable : ");
    Serial.println(GetIntEn(), 2);

    /*SetMaxDurCalConfig(LO, LO);
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
    Serial.println(rpt_sl, 2);*/

    /*SetAccelEN(HI);
    SetProxEN(HI); //On Proximity*/

    Serial.println("---------CAP1114 initialization End-----------");
    Serial.println();
    //SetMSControl(MSControl::INT, LO);
  }
}

Sessami_Button::~Sessami_Button() {

}

#endif
