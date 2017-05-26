/**************************************************************************************
  Title : Sessami CAP1114 Thermostat class
  Created by : Kaz Wong
  Date : 7 Dec 2016
  Description : class for handle Thermostat
 ***************************************************************************************/

#ifndef SESSAMI_THERMOSTAT_H_
#define SESSAMI_THERMOSTAT_H_

class Thermostat {
  private:
    static uint8_t th_idx;
    static string aircon_mode[];    
    static float temp_setpoint;
  public:
    void SetAMode(uint8_t idx);
    uint8_t GetAMode();
    string GetAModeS();

    float GetTempSetPt();
    void SetTempSetPt(float value);

    float operator++();
    float operator--();
    float operator++(int);
    float operator--(int);
};

uint8_t Thermostat::th_idx = 0;
string Thermostat::aircon_mode[] = {"Cooling Active", "Cooling Notact", "Heating Active", "Heating Notact", "Auto", "Dhumidity", "Humidity"};
float Thermostat::temp_setpoint = 25.5;

void Thermostat::SetAMode(uint8_t _idx) {
  th_idx = _idx;
}

uint8_t Thermostat::GetAMode() {
  return th_idx;
}

string Thermostat::GetAModeS() {
  return aircon_mode[th_idx];
}

float Thermostat::GetTempSetPt() {
  return temp_setpoint;
}

void Thermostat::SetTempSetPt(float value) {
  temp_setpoint = value;
}

float Thermostat::operator++() {
  temp_setpoint += 0.1;
  return temp_setpoint;
}

float Thermostat::operator--() {
  temp_setpoint  -= 0.1;
  return temp_setpoint;
}
float Thermostat::operator++(int) {
  float tmp = temp_setpoint;
  operator++();
  return tmp;
}
float Thermostat::operator--(int) {
  float tmp = temp_setpoint;
  operator--();
  return tmp;
}

#endif
