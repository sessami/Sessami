/**************************************************************************************
  Title : Sessami controller
  Created by : Kaz Wong
  Date : 7 Dec 2016
  Description : Core class for Sessami, control the system state
 ***************************************************************************************/

#ifndef SESSAMI_CONTROLLER_H_
#define SESSAMI_CONTROLLER_H_

#include <Arduino.h>
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include <TimeLib.h>

#include <OpenWeather_ESP8266.h>
#include <WifiManage.h>
#include <Si7020.h>
#include "CAP1114_Button.h"
#include "CAP1114_LED.h"

#include "SessamiUI.h"
#include "CAP1114_TouchController.h"
//#include "TemperatureHumidity_Si7006A20.h"

#include "Sessami_Page_Standby.h"
#include "Sessami_Page_Normal.h"
#include "Sessami_Page_StbNor.h"
#include "Sessami_Page_Grid.h"
#include "Sessami_Page_Blank.h"
#include "Sessami_Page_KeypadTest.h"
#include "Sessami_Page_ButtonSen.h"

#define SESSAMI_SDA 2
#define SESSAMI_SCL 0

const int NTP_PACKET_SIZE = 48; // NTP time is in the first 48 bytes of message
WiFiUDP Udp;

 tmElements_t _time;

time_t getNtpTime();
void sendNTPpacket(IPAddress &address, byte *packet_buffer);

//---------------------------------Class Definition-------------------------------
class SessamiController {
  private:
    time_t prev_sec;
    time_t sec_counter;
    time_t min_counter;
    time_t hr_counter;
    uint8_t state, last_state;
    static int time_zone;
    static bool interrupt;
    bool ui_rst;
    bool engg_mode;
    TouchController *tc;
    Sessami_Button *button;
    Sessami_LED *led;
    WifiManage wifi;
    Si7020 temp_sensor;
    SessamiUI *ui[2];
    
    //For Develop
    SessamiUI *engg_ui[6];

    OpenWeather_ESP8266 openweather;
    unsigned long interval_ow;

    void Normal();
    void ENGG();
  public:
    /*****************************************************************************************
     *  This is the function for update
    ******************************************************************************************/
    static void Interrupt();
    void Background();
    void Mode();

    static int GetTimeZone() {
      return time_zone;
    }

    SessamiController();
    ~SessamiController();
};

//---------------------------------Static Variable-------------------------------
int SessamiController::time_zone = 8;
bool SessamiController::interrupt = false;

//---------------------------------Constructor & Destructor-------------------------------
SessamiController::SessamiController() :
  state(0), ui_rst(true), engg_mode(false), prev_sec(0), sec_counter(0), min_counter(0), hr_counter(0) {

//Setup Serial port, I2C, network
  Serial.begin(115200);
  while (!Serial) {
    ;  //wait for serial port to initialize
  }

  Wire.begin(SESSAMI_SDA, SESSAMI_SCL);
  delay(500);
  wifi.initWiFiConnection();

  Udp.begin(8888);
  Serial.println("waiting for sync");
  setSyncProvider(getNtpTime);
  setSyncInterval((time_t)300);
  
//Initialize variable
  _time.Second = second();
  _time.Minute = minute();
  _time.Hour = hour();

  tc = new TouchController;
  button = new Sessami_Button;
  led = new Sessami_LED;

  tc->Update();
  openweather.Update();
  temp_sensor.UpdateRH();
  temp_sensor.UpdateTp();

  interval_ow = 1;

  ui[0] = (SessamiUI *)new Page_Standby;
  ui[1] = (SessamiUI *)new Page_Normal;
  //ui[2] = (SessamiUI *)new Page_StbNor;

  //For Develop
  engg_ui[0] = (SessamiUI *)new Page_Standby;
  engg_ui[1] = (SessamiUI *)new Page_Normal;
  engg_ui[2] = (SessamiUI *)new Page_Grid;
  engg_ui[3] = (SessamiUI *)new Page_KeypadTest;
  engg_ui[4] = (SessamiUI *)new Page_ButtonSen;
  engg_ui[5] = (SessamiUI *)new Page_Blank;
}

SessamiController::~SessamiController() {
}

#endif

