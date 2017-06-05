#ifndef SESSAMI_UI_H_
#define SESSAMI_UI_H_

#include "Arduino.h"

#include "ImageDraw_ESP8266.h"
//#include "SessamiButton.h"

#include "Fonts/LiberationSans_Regular2pt7b.h"
#include "Fonts/LiberationSans_Regular4pt7b.h"
#include "Fonts/LiberationSans_Regular6pt7b.h"
#include "Fonts/LiberationSans_Regular8pt7b.h"
#include "Fonts/LiberationSans_Regular10pt7b.h"
#include "Fonts/LiberationSans_Regular12pt7b.h"
#include "Fonts/LiberationSans_Regular14pt7b.h"
#include "Fonts/LiberationSans_Regular16pt7b.h"
#include "Fonts/LiberationSans_Regular18pt7b.h"
#include "Fonts/LiberationSans_Regular20pt7b.h"
#include "Fonts/LiberationSans_Regular24pt7b.h"
#include "Fonts/LiberationSans_Regular26pt7b.h"
#include "Fonts/LiberationSans_Regular28pt7b.h"
#include "Fonts/LiberationSans_Regular40pt7b.h"
#include "Fonts/LiberationSans_Regular42pt7b.h"
#include "Fonts/LiberationSans_Regular44pt7b.h"
#include "Fonts/LiberationSans_Regular46pt7b.h"
#include "Fonts/LiberationSans_Regular48pt7b.h"

// For the Adafruit shield, these are the default.
#define TFT_DC 2
#define TFT_CS 15

class UI_ESP8266 {
protected:
	static ImageDraw_ESP8266 *image_draw;
	static Adafruit_ILI9341 tft;
	//static Button b;
	static unsigned int src_rate;
	unsigned long ui_t;
	uint8_t state;
public:
	static void initScr();
	virtual void UIStateMachine(bool rst);

	static char* Input();
	static void Keyboard();
	virtual void Main();

	UI_ESP8266();
	virtual ~UI_ESP8266();
};

Adafruit_ILI9341 UI_ESP8266::tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
ImageDraw_ESP8266 *UI_ESP8266::image_draw = new ImageDraw_ESP8266(tft);
//Button UI_ESP8266::b;
unsigned int UI_ESP8266::src_rate = 5000;

UI_ESP8266::UI_ESP8266() : state(0), ui_t(0) {

}

UI_ESP8266::~UI_ESP8266() {
	delete image_draw;
}



#endif
