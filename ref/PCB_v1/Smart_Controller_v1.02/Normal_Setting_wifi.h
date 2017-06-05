#include "SessamiUI.h"
#include "WifiManage.h"

class Normal_Setting_wifi: UI_ESP8266 {
private:
	WifiManage wifi;
public:
	virtual void Src();
	virtual void Menu();

	Normal_Setting_wifi(SmartTouch_ESP8266 _st, WifiManage _wifi);
	~Normal_Setting_wifi();
};

Normal_Setting_wifi::Normal_Setting_wifi(SmartTouch_ESP8266 _st, WifiManage _wifi) : UI_ESP8266(_st), wifi(_wifi) {

}

Normal_Setting_wifi::~Normal_Setting_wifi() {

}

virtual void Src() {

}

virtual void Menu() {

}
