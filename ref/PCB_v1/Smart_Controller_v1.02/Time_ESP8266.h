//From Arduino library TimeNTP.ino

#ifndef TIMEESP8266_H_
#define TIMEESP8266_H_

#include <TimeLib.h>
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include <SPI.h>

const int NTP_PACKET_SIZE = 48; // NTP time is in the first 48 bytes of message

class Time_ESP8266 {
  private:
    static int time_zone;
    static IPAddress *time_server;
    static WiFiUDP Udp;
    static byte packet_buffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets
    unsigned int local_port;

  public:
    static time_t getNtpTime();
    static void sendNTPpacket(IPAddress &address);
    void initTime();

    Time_ESP8266();
    ~Time_ESP8266();
};

int Time_ESP8266::time_zone = 8;
IPAddress *Time_ESP8266::time_server = new IPAddress[3];
WiFiUDP Time_ESP8266::Udp;
byte Time_ESP8266::packet_buffer[NTP_PACKET_SIZE]; 

Time_ESP8266::Time_ESP8266() : local_port(8888) {
  time_server[0] = IPAddress(132, 163, 4, 101);
  time_server[1] = IPAddress(132, 163, 4, 102);
  time_server[2] = IPAddress(132, 163, 4, 103);
}
Time_ESP8266::~Time_ESP8266() {
}

#endif
