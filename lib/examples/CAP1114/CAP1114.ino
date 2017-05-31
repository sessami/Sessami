#include <Arduino.h>
#include <TimeLib.h>

#include "CAP1114_Button.h"
#include "CAP1114_LED.h"
#include "CAP1114_Driver.h"

#define SESSAMI_SDA 2
#define SESSAMI_SCL 0

#define TFT_DC 16
#define TFT_CS 4

tmElements_t _time;
uint8_t debug;
uint8_t debug2;

//button constructor needs I2C connection 
Sessami_Button *button;

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ;  //wait for serial port to initialize
  }
  Wire.begin(SESSAMI_SDA, SESSAMI_SCL);
  //create button object after I2C setup
  button = new Sessami_Button;
}

void loop() {
  Background();
  button->UpdateBut();

  ButTest();
}

void Background() {
  if (second() != _time.Second) {
    //Update per second
    button->HeldCount();
    button->HoldCount();
  }
}

void ButTest() {
  if (*button == B_UP)
    Serial.println("UP");
}

