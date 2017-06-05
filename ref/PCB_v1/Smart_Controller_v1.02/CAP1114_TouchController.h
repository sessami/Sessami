#ifndef CAP1114_TOUCHCONTROLLER_H_
#define CAP1114_TOUCHCONTROLLER_H_

#include "CAP1114_Driver.h"

using namespace CAP1114;

class TouchController: protected CAP1114_Driver {
public:
	TouchController();
	~TouchController();

	void Toggle();
};

TouchController::TouchController() :
		CAP1114_Driver() {
	bool sg, gp;
	uint8_t rpt_ph, m_press, max_dur, rpt_sl;

	Serial.println("---------CAP1114 initialization Start-----------");

	if (!initWireI2C())
		Serial.println("CAP1114 communication fail!");
	else {
		//--------------------------------CAP1114 initialization -----------------------------
		SetIntEn(0xFF); //interrupt Enable
		//touch_cap->SetGroupIntEN(HI);
		Serial.print("Interrupt Enable : ");
		Serial.println(GetIntEn(), 2);

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

		SetGPIODir(B11011111);
		Serial.print("GPIO Direction: ");
		Serial.println(GetGPIODir(), 2);

		SetLEDLinking(B7 | B4 | B3 | B2);
		SetAccelEN(HI);
		SetProxEN(HI); //On Proximity
		SetProxSen(1); //Set Sensivity
		SetCalAct(0xFF); //Calibrate all Sensor
		SetMSControl(MSControl::INT, LO);
		SetLED(0);

		Serial.println("---------CAP1114 initialization End-----------");
		Serial.println();
	}
}

TouchController::~TouchController() {
}

#endif
