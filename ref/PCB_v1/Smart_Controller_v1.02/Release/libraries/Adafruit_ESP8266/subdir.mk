################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
C:\Program\ Files\eclipse\arduinoPlugin\libraries\Adafruit_ESP8266\1.0.0\Adafruit_ESP8266.cpp 

LINK_OBJ += \
.\libraries\Adafruit_ESP8266\Adafruit_ESP8266.cpp.o 

CPP_DEPS += \
.\libraries\Adafruit_ESP8266\Adafruit_ESP8266.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
libraries\Adafruit_ESP8266\Adafruit_ESP8266.cpp.o: C:\Program\ Files\eclipse\arduinoPlugin\libraries\Adafruit_ESP8266\1.0.0\Adafruit_ESP8266.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Program Files\eclipse\arduinoPlugin\tools\esp8266\xtensa-lx106-elf-gcc\1.20.0-26-gb404fb9-2/bin/xtensa-lx106-elf-g++" -D__ets__ -DICACHE_FLASH -U__STRICT_ANSI__ "-IC:/Program Files/eclipse/arduinoPlugin/packages/esp8266/hardware/esp8266/2.3.0/tools/sdk/include" "-IC:/Program Files/eclipse/arduinoPlugin/packages/esp8266/hardware/esp8266/2.3.0/tools/sdk/lwip/include" "-IC:/Users/Carson/Desktop/workspace/Smart_Controller/Release/core" -c -Os -g -mlongcalls -mtext-section-literals -fno-exceptions -fno-rtti -falign-functions=4 -std=c++11 -MMD -ffunction-sections -fdata-sections -DF_CPU=80000000L -DLWIP_OPEN_SRC  -DARDUINO=10609 -DARDUINO_ESP8266_NODEMCU -DARDUINO_ARCH_ESP8266 "-DARDUINO_BOARD=\"ESP8266_NODEMCU\"" -DESP8266  -I"C:\Program Files\eclipse\arduinoPlugin\packages\esp8266\hardware\esp8266\2.3.0\cores\esp8266" -I"C:\Program Files\eclipse\arduinoPlugin\packages\esp8266\hardware\esp8266\2.3.0\variants\nodemcu" -I"C:\Program Files\eclipse\arduinoPlugin\packages\esp8266\hardware\esp8266\2.3.0\libraries\Wire" -I"C:\Program Files\eclipse\arduinoPlugin\packages\esp8266\hardware\esp8266\2.3.0\libraries\SPI" -I"C:\Program Files\eclipse\arduinoPlugin\packages\esp8266\hardware\esp8266\2.3.0\libraries\ESP8266WiFi" -I"C:\Program Files\eclipse\arduinoPlugin\packages\esp8266\hardware\esp8266\2.3.0\libraries\ESP8266WiFi\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Adafruit_ILI9341\1.0.2" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Time\1.5.0" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\TimeAlarms\1.5.0" -I"C:\Program Files\eclipse\arduinoPlugin\packages\esp8266\hardware\esp8266\2.3.0\libraries\esp8266" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Adafruit_GFX_Library\1.1.3" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\AVR_Standard_C_Time_Library\1.8.0-4" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\AVR_Standard_C_Time_Library\1.8.0-4\src" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\ArduinoJson\5.6.7" -I"C:\Program Files\eclipse\arduinoPlugin\libraries\Adafruit_ESP8266\1.0.0" -I"C:\Program Files\eclipse\arduinoPlugin\packages\esp8266\hardware\esp8266\2.3.0\libraries\esp8266\src" -I"C:\Program Files\eclipse\arduinoPlugin\packages\esp8266\hardware\esp8266\2.3.0\libraries\SoftwareSerial" -I"C:\Users\Carson\Desktop\workspace\Smart_Controller\Fonts" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<" -o "$@"  -Wall
	@echo 'Finished building: $<'
	@echo ' '


