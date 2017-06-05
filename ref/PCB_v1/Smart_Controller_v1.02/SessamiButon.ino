#include "SessamiButton.h"

bool Button::operator==(ButtonEnum button) {
	if ((button_state & (uint8_t)button) > 0)
		return true;
	return false;
}

bool Button::operator==(SlideEnum slide) {
	if ((slide_state & (uint8_t)slide) > 0)
		return true;
	return false;
}

void Button::UpdateBut() {
	uint16_t mask = 0;
	uint16_t cs;

	UpdateSlide();
	slide_state = GetSlide();

	UpdateCS();
	cs = GetCS();
	mask |= (uint8_t)CS::CS1 | (uint8_t)CS::CS2 | (uint8_t)CS::CS3 | (uint8_t)CS::CS4 | (uint8_t)CS::CS5 | (uint8_t)CS::CS6;

	button_state = (uint8_t) cs & mask;
	button_state |= (uint8_t) ((cs & (uint8_t)CS::CS7) >> 2);

	SetMSControl(MSControl::INT, LO);
}

uint8_t Button::GetBut() {
	return button_state;
}

uint8_t Button::GetSli() {
	return slide_state;
}
