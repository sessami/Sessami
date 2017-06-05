#include "SessamiUI.h"

void UI_ESP8266::initScr() {
	image_draw->initLCD();
	image_draw->ClearLCD();
}

void UI_ESP8266::Main() {
	image_draw->ClearLCD();
 delay(50);

  tft.drawLine(0,0,319,0,ILI9341_WHITE); //Horizontal partition
  delay(50);
  tft.drawLine(0,239,319,239,ILI9341_WHITE); //Horizontal partition
  delay(50);
  tft.drawLine(0,0,0,239,ILI9341_WHITE); //Vertical partition
  delay(50);
  tft.drawLine(319,0,319,239,ILI9341_WHITE); //Vertical partition
  delay(50);

  tft.setFont(&LiberationSans_Regular48pt7b);
	tft.setCursor(55, 100);
	tft.print("Hello");

 tft.setCursor(35, 200);
 tft.print("World");
 delay(50);
}

void UI_ESP8266::UIStateMachine(bool rst) {
	if (rst)
		state = 0;
	switch (state) {
	case 0:
		//if (b == ButtonEnum::MID)
			//state = 1;
		//if (millis() - ui_t >= src_rate) {
			Main();
     Serial.println("Main UI");
     
     //ui_t = millis();
		//}
		break;
	case 1:
		//if (b == ButtonEnum::MID)
			//state = 0;
		if (millis() - ui_t >= src_rate) {
			Keyboard();
			Input();

      ui_t = millis();
		}
		break;
	}
}

void UI_ESP8266::Keyboard() {
	tft.setFont(&LiberationSans_Regular28pt7b);
	tft.setTextColor(ILI9341_WHITE);
	tft.setCursor(180, 60);
	tft.print("a");

	tft.setCursor(190, 70);
	tft.print("b");
}

char* UI_ESP8266::Input() {
	char key = 'a';

	Keyboard();
	return &key;
}
