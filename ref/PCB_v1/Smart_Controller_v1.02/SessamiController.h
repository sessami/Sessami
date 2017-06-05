#ifndef SESSAMI_CONTROLLER_H_
#define SESSAMI_CONTROLLER_H_

//#include "SPI.h"
//#include <Adafruit_GFX.h>
//#include <Adafruit_ILI9341.h>
#include <Arduino.h>

//#include "OpenWeather_ESP8266.h"
#include "SessamiUI.h"
#include "CAP1114_TouchController.h"
//#include "TemperatureHumidity_Si7006A20.h"
//#include "Time_ESP8266.h"
//#include "WifiManage.h"

class SessamiController {
private:
	uint8_t state;
  bool rst, ui_rst;

	TouchController tc;
	UI_ESP8266 ui;
public:
	void Background();
	void StateMachine();

	SessamiController();
	~SessamiController();
};

SessamiController::SessamiController() :
		state(0), rst(false), ui_rst(false) {
	  ui.initScr();

   ui.UIStateMachine(ui_rst);
}
SessamiController::~SessamiController() {
}

#endif
