/**************************************************************************************
 Title : Display 24-bit Bitmap Image from 4MB ESP-12E Flash on TFT LCD using ILI9341 driver
 Modified by : Sagar Naikwadi
 Date : 7th Sep 2016
 Version : 0.1
 Description : Works with the 24-bit BMP image to display on TFT LCD screen connected to ESP
 ***************************************************************************************/

#ifndef WIFIMANAGE_H_
#define WIFIMANAGE_H_

#include <String>

class WifiManage {
private:
	String ssid; //Wi-Fi SSID for ESP8266
	String password; //Wi-Fi Password for ESP8266

public:
	void SetSSID(String _ssid) { ssid = _ssid; }
	void SetPW(String _password) { password = PWCry(_password); }
	const char* PWCry(String pw) { return pw.c_str(); }
	const char* PWCry() { return password.c_str(); }

	String GetSSID() const { return ssid; }
	String GetPW() const { return password; }
	//Static member function
	bool initWiFiConnection();

	WifiManage();
	~WifiManage();
};

WifiManage::WifiManage() {
	SetSSID("Coolsure");
	SetPW("abcdeabcde");
}

WifiManage::~WifiManage() {
}

#endif
