/**************************************************************************************
  Title : Sessami Main Sketch
  Created by : Kaz Wong
  Date : 7 Dec 2016
  Description : entry function for Sessami
 ***************************************************************************************/

#include <Arduino.h>
#include "SessamiController.h"

volatile unsigned long int_t = 0;
volatile unsigned long rp_int = 0;

SessamiController *c;

void Toggle() {
  rp_int = micros() - int_t;
  int_t = micros();
  c->Interrupt();
}

void setup() {
  c = new SessamiController();

  pinMode(5, INPUT);
  attachInterrupt(digitalPinToInterrupt(5), Toggle, FALLING);
}

void loop() {
  c->Background();
  c->Mode();
}

