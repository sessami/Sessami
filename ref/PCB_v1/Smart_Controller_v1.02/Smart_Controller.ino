/**************************************************************************************
 Original Contributor Information
 Sample Arduino Json Web Client
 Downloads and parse http://jsonplaceholder.typicode.com/users/1
 Copyright Benoit Blanchon 2014-2016
 MIT License
 Arduino JSON library
 https://github.com/bblanchon/ArduinoJson
 If you like this project, please add a star!
 ***************************************************************************************/
/**************************************************************************************
 Title : OpenWeather + ESP8266 + Display ousing AdafruitILI9341
 Modified by : Sagar Naikwadi
 Date : 19th Sep 2016
 Version : 0.1
 Description : Works well with openweather upload and download with JSON format and display on screen
 ***************************************************************************************/
 
#include <Arduino.h>
#include "SessamiController.h"

SessamiController *c;

void Toggle() {
	Serial.print("hihi you");
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ;  //wait for serial port to initialize
  }

	c = new SessamiController();

  pinMode(12, INPUT);
  attachInterrupt(digitalPinToInterrupt(12), Toggle, RISING);
}

void loop() {
	c->StateMachine();
	c->Background();
}

