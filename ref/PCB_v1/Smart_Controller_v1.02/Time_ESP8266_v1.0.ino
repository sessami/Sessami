//From Arduino library TimeNTP.ino

#include "Time_ESP8266.h"
#include <TimeLib.h>

void Time_ESP8266::initTime() {
  Udp.begin(local_port);
  Serial.println("waiting for sync");
  setSyncProvider(getNtpTime);
}

time_t Time_ESP8266::getNtpTime()
{
  while (Udp.parsePacket() > 0) ; // discard any previously received packets
  Serial.println("Transmit NTP Request");
  sendNTPpacket(time_server[0]);
  uint32_t beginWait = millis();
  while (millis() - beginWait < 1500) {
    Serial.print(".");
    int size = Udp.parsePacket();
    if (size >= NTP_PACKET_SIZE) {
      Serial.println();
      Serial.println("Receive NTP Response");
      Udp.read(packet_buffer, NTP_PACKET_SIZE);  // read packet into the buffer
      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 =  (unsigned long)packet_buffer[40] << 24;
      secsSince1900 |= (unsigned long)packet_buffer[41] << 16;
      secsSince1900 |= (unsigned long)packet_buffer[42] << 8;
      secsSince1900 |= (unsigned long)packet_buffer[43];
      return secsSince1900 - 2208988800UL + time_zone * SECS_PER_HOUR;
    }
  }
  Serial.println();
  Serial.println("No NTP Response :-(");
  return 0; // return 0 if unable to get the time
}

void Time_ESP8266::sendNTPpacket(IPAddress &address)
{
  // set all bytes in the buffer to 0
  memset(packet_buffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packet_buffer[0] = 0b11100011;   // LI, Version, Mode
  packet_buffer[1] = 0;     // Stratum, or type of clock
  packet_buffer[2] = 6;     // Polling Interval
  packet_buffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packet_buffer[12]  = 49;
  packet_buffer[13]  = 0x4E;
  packet_buffer[14]  = 49;
  packet_buffer[15]  = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packet_buffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}
