#ifndef SESSAMI_BUTTON_H_
#define SESSAMI_BUTTON_H_

#include "CAP1114_Driver.h"

using namespace CAP1114;

enum class ButtonEnum {
    PROX = B0,
    MID = B1,
    LEFT = B2,
    UP = B3,
    POWER = B4,
    DOWN = B5,
    RIGHT = B6
  };

enum class SlideEnum {
    PH = B0, TAP = B1, DOWN = B2, UP = B3, RESET = B5, MULT = B6, LID = B7
  };

class Button: private CAP1114_Driver {
private:
	uint8_t button_state;
	uint8_t slide_state;
public:
	Button();
	~Button();

	bool operator==(ButtonEnum button);
	bool operator==(SlideEnum slide);

	void UpdateBut();
	uint8_t GetBut();
	uint8_t GetSli();

	/*state GetPROX();
	 state GetMID();
	 state GetLEFT();
	 state GetUP();
	 state GetPOWER();
	 state GetDOWN();
	 state GetRIGHT();
	 state GetSLL();
	 state GetSLR();*/
};

Button::Button() :
		CAP1114_Driver(), button_state(0), slide_state(0) {

}

Button::~Button() {

}

#endif
