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

enum class ButtonEnum {PROX = B0,
  MID = B5,
  LEFT = B6,
  UP = B1,
  POWER = B3,
  DOWN = B2,
  RIGHT = B4
};

enum class SlideEnum {
  PH = B0, TAP = B1, RIGHT = B2, LEFT = B3, RESET = B5, MULT = B6, LID = B7
};

#define B_PROX 1 //Sensor 1
#define B_MID 32 //Sensor 6
#define B_LEFT 64 //Sensor 7
#define B_UP 2 //Sensor 2
#define B_POWER 8 //Sensor 4
#define B_DOWN 4 //Sensor 3
#define B_RIGHT 16 //Sensor 5

#define S_PH 257
#define S_TAP 258
#define S_RIGHT 260
#define S_LEFT 264
#define S_RESET 288
#define S_MULT 320

class Sessami_Button: private CAP1114_Driver {
  private:
    static uint8_t button_state;
    static uint8_t slide_state;
    static unsigned long held_t;
    static unsigned int button_tap;
    static uint8_t delta_sen;
    static uint8_t prox_sen;
    static uint8_t threshold[8];
    static int8_t delta_count[8];
  public:
    Sessami_Button();
    ~Sessami_Button();

    bool operator==(const ButtonEnum button) const;
    bool operator==(const SlideEnum slide) const;
    bool operator==(const unsigned int key) const;

    void UpdateBut();
    uint8_t GetBut();
    uint8_t GetSli();
    unsigned long GetHeldT();
    void HeldCount();
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
unsigned int Sessami_Button::button_tap = 0;
uint8_t Sessami_Button::delta_sen = 4; //0-most, 7-least
uint8_t Sessami_Button::prox_sen = 4; //0-most, 7-least
uint8_t Sessami_Button::threshold[8] = {0, 0, 0, 0,   0, 0, 0, 0};
int8_t Sessami_Button::delta_count[8] = {0, 0, 0, 0,   0, 0, 0, 0};

Sessami_Button::Sessami_Button() :
  CAP1114_Driver() {
    
}

Sessami_Button::~Sessami_Button() {

}

#endif
