/**************************************************************************************
  Title : Sessami controller
  Created by : Kaz Wong
  Date : 7 Dec 2016
  Description : Core class for Sessami, control the system state
 ***************************************************************************************/

#include "SessamiController.h"
#include "CAP1114_LED.h"

void SessamiController::Interrupt() {
  interrupt = true;
}

void SessamiController::Background() {
  ui[state]->EvLoop();
  if (second() != _time.Second) {
    sec_counter++;
    _time.Second = second();
    //Update per second
    button->HeldCount();
    button->HoldCount();
    ui[state]->EvSec();
    if (minute() != _time.Minute) {
      min_counter++;
      _time.Minute = minute();
      //Update per minute
      temp_sensor.UpdateRH();
      temp_sensor.UpdateTp();
      ui[state]->EvMin();
      if (hour() != _time.Hour) {
        hr_counter++;
        _time.Hour = hour();
        //Update per hour
        if (hr_counter % interval_ow == 0)
          openweather.Update();
        ui[state]->EvHr();
      }
    }
  }
}

void SessamiController::Normal() {
  switch (state) {
    case 0 : 
      if (*button == B_PROX) {
        led->SetDutyCycle(B1111, B110);
        state = 1;
        ui_rst = true;
      }
      break;
    case 1 : 
      if (button->GetHeldT() > 3) {
        led->SetDutyCycle(B1111, B000);
        state = 0;
        ui_rst = true;
      }
      break;
  }
  
  ui[state]->UIStateMachine(ui_rst);
}

void SessamiController::Mode() {
  button->UpdateBut();

   if ( (*button == B_LEFT) && (*button == B_UP) ) {
    engg_mode = !engg_mode; // engineering mode
    state = 0;
    ui_rst = true;
    engg_ui[5]->UIStateMachine(ui_rst);
    delay(1000);
   }
        
  if (!engg_mode)
    Normal();
  else
    ENGG();
    
  ui_rst = false;
  if (interrupt) {
    interrupt = false;
  }
}

void SessamiController::ENGG() {
  switch (state) {
    case 0 :
       if ( (*button == B_UP) && (*button == B_DOWN) ) {
        state = 1;
        ui_rst = true;
      } else if ( (*button == B_LEFT) && (*button == B_POWER ) ) {
        state = 2;
        last_state = 0;
        ui_rst = true;
      }  else if ( (*button == B_LEFT) && (*button == B_RIGHT ) ) {
        state = 3;
        ui_rst = true;
      }
      break;
    case 1 :
      if ( (*button == B_UP) && (*button == B_DOWN) ) {
        state = 0;
        ui_rst = true;
      } else if ( (*button == B_LEFT) && (*button == B_POWER ) ) {
        state = 2;
        last_state = 1;
        ui_rst = true;
      } else if ( (*button == B_LEFT) && (*button == B_RIGHT ) ) {
        state = 3;
        ui_rst = true;
      }
      break;
    case 2 :
      if (button->BuTap() ) {
        state = last_state;
        ui_rst = true;
      }
      break;
    case 3 :
      if ( (*button == B_LEFT) && (*button == B_RIGHT ) ) {
        state = 4;
        ui_rst = true;
      } else if ( (*button == B_LEFT) && (*button == B_POWER ) ) {
        state = 2;
        last_state = 3;
        ui_rst = true;
      }
      break;
    case 4 :
      if ( (*button == B_LEFT) && (*button == B_RIGHT ) ) {
        state = 0;
        ui_rst = true;
      } else if ( (*button == B_LEFT) && (*button == B_POWER ) ) {
        state = 2;
        last_state = 4;
        ui_rst = true;
      }
      break;
  }

  engg_ui[state]->UIStateMachine(ui_rst);
}

time_t getNtpTime() {
  byte packet_buffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets
  IPAddress time_server(132, 163, 4, 101);

  while (Udp.parsePacket() > 0) ; // discard any previously received packets
  Serial.println("Transmit NTP Request");
  sendNTPpacket(time_server, packet_buffer);
  uint32_t beginWait = millis();
  while (millis() - beginWait < 1500) {
    Serial.print(".");
    int size = Udp.parsePacket();
    if (size >= NTP_PACKET_SIZE) {
      Serial.println("Receive NTP Response");
      Udp.read(packet_buffer, NTP_PACKET_SIZE);  // read packet into the buffer
      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 =  (unsigned long)packet_buffer[40] << 24;
      secsSince1900 |= (unsigned long)packet_buffer[41] << 16;
      secsSince1900 |= (unsigned long)packet_buffer[42] << 8;
      secsSince1900 |= (unsigned long)packet_buffer[43];
      return secsSince1900 - 2208988800UL + SessamiController::GetTimeZone() * SECS_PER_HOUR;
    }
  }
  Serial.println("No NTP Response :-(");
  return 0; // return 0 if unable to get the time
}

void sendNTPpacket(IPAddress & address, byte * packet_buffer) {
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
