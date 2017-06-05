/**************************************************************************************
 Original Contributor Information
  This is our Bitmap drawing example for the Adafruit ILI9341 Breakout and Shield
  ----> http://www.adafruit.com/products/1651

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
***************************************************************************************/
/**************************************************************************************
 Title : Display 24-bit Bitmap Image from 4MB ESP-12E Flash on TFT LCD using ILI9341 driver
 Modified by : Sagar Naikwadi
 Date : 7th Sep 2016
 Version : 0.1
 Description : Works with the 24-bit BMP image to display on TFT LCD screen connected to ESP
***************************************************************************************/

#include "WifiManage.h" 

//Initialize WiFi Connection
bool WifiManage::initWiFiConnection()
{                 
             Serial.println("---------Wi-Fi Connection Start-----------");     
               
             Serial.print("Using Wi-Fi SSID :");
             Serial.println(ssid);
   
            WiFi.begin(ssid.c_str(), PWCry());
            Serial.println("\nAttempting Connection!!!");
            
            while (WiFi.status() != WL_CONNECTED) 
            {
                      delay(500);
                      Serial.print(".");
            }
            Serial.println("");
            Serial.println("Wi-Fi connected to SSID :");
            Serial.println(ssid.c_str());
            Serial.println("IP address :");
            Serial.println(WiFi.localIP());

            Serial.println("---------Wi-Fi Connection End-----------");   
            Serial.println();
            return true;    
}

