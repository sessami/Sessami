/***************************************************
 Begin Date : 2nd August 2016
 DescriptiHI : Register Header file for CAP1114
 Original Source : Adafruit_CAP1188.h Link: https://github.com/adafruit/Adafruit_CAP1188_Library/archive/master.zip
 Datasheet Link : http://ww1.microchip.com/downloads/en/DeviceDoc/CAP1114.pdf
 Modifier : Sagar Naikwadi
 ****************************************************/
// Referred from Adafruit cHItributors for CAP1118
/***************************************************
 This is a library for the CAP1188 8-Channel Capacitive Sensor

 Designed specifically to work with the CAP1188 breakout from Adafruit
 ----> https://www.adafruit.com/products/1602

 These sensors use I2C/SPI to communicate, 2+ pins are required to interface
 Adafruit invests time and resources providing this open source code,
 please support Adafruit and open-source hardware by purchasing
 products from Adafruit!

 Written by Limor Fried/Ladyada for Adafruit Industries.
 BSD license, all text above must be included in any redistributiHI
 ****************************************************/
#ifndef CAP1114_DRIVER_H_
#define CAP1114_DRIVER_H_

#include "I2CSensor.h"
#include "CAP1114_Registers.h"

namespace CAP1114 {

#define SLIPOS_CS8   0x02
#define SLIPOS_CS9   0x12
#define SLIPOS_CS10 0x22
#define SLIPOS_CS11 0x32
#define SLIPOS_CS12 0x42
#define SLIPOS_CS13 0x52
#define SLIPOS_CS14 0x62

enum class MSControl {
    INT = B0, PWR_LED = B1, DSLEEP = B4, SLEEP = B5, DEACT = B6
  };
  enum class LED {
    LED1 = B0, LED2 = B1, LED3 = B2, LED4 = B3, LED5 = B4, LED6 = B5, LED7 = B6, LED8 = B7, LED9 = HB|B0, LED10 = HB|B1, LED11 = HB|B2,
  };
    enum class CS {
    CS1 = B0,
    CS2 = B1,
    CS3 = B2,
    CS4 = B3,
    CS5 = B4,
    CS6 = B5,
    DOWN = B6,
    UP = B7,
    CS7 = HB|B0,
    CS8 = HB|B1,
    CS9 = HB|B2,
    CS10 = HB|B3,
    CS11 = HB|B4,
    CS12 = HB|B5,
    CS13 = HB|B6,
    CS14 = HB|B7
  };
  enum class Slide {
    PH = B0, TAP = B1, DOWN = B2, UP = B3, RESET = B5, MULT = B6, LID = B7
  };

  enum class SDelta {
    CS1 = 0x10,
    CS2 = 0x11,
    CS3 = 0x12,
    CS4 = 0x13,
    CS5 = 0x14,
    CS6 = 0x15,
    CS7 = 0x16,
    CS8 = 0x17,
    CS9 = 0x18,
    CS10 = 0x19,
    CS11 = 0x1A,
    CS12 = 0x1B,
    CS13 = 0x1C,
    CS14 = 0x1D
  };
    enum class LEDLinking {
    CS1 = B0,
    CS2 = B1,
    CS3 = B2,
    CS4 = B3,
    CS5 = B4,
    CS6 = B5,
    CS7 = B6,
    Group = B7
  };

    enum class IntEn {
    S1 = B0,
    S2 = B1,
    S3 = B2,
    S4 = B3,
    S5 = B4,
    S6 = B5,
    S7 = B6,
    G = B7,
    GPIO1 = HB|B0,
    GPIO2 = HB|B1,
    GPIO3 = HB|B2,
    GPIO4 = HB|B3,
    GPIO5 = HB|B4,
    GPIO6 = HB|B5,
    GPIO7 = HB|B6,
    GPIO8 = HB|B7
  };

  enum class GPIODir {
    LED1_DIR = B0,
    LED2_DIR = B1,
    LED3_DIR = B2,
    LED4_DIR = B3,
    LED5_DIR = B4,
    LED6_DIR = B5,
    LED7_DIR = B6,
    LED8_DIR = B7
  };

class CAP1114_Driver: private I2CSensor {
public: //protected:
	CAP1114_Driver();
	virtual ~CAP1114_Driver();
	virtual State initWireI2C();

	/*
	 73h, 74h RW - LED Output CHItrol Registers
	 LED8_DR | LED7_DR | LED6_DR | LED5_DR | LED4_DR | LED3_DR | LED2_DR | LED1_DR
	 - | - | - | - | - | LED11_DR | LED10_DR | LED9_DR
	 */
private:
	static uint8_t st_73, st_74;
protected:
	void UpdateLED(uint8_t *status1 = 0, uint8_t *status2 = 0);
	State GetLED(LED b) const;
	void SetLED(uint16_t value);
	void SetLED(LED b, State st);

	/*
	 00h RW - Main Status CHItrol Registers
	 - | DEACT | SLEEP | DSLEEP | - | - | PWR_LED | INT
	 */
private:
	static uint8_t st_00;
protected:
	void UpdateMSControl(uint8_t *status = 0);
	State GetMSControl(MSControl b) const;
	void SetMSControl(uint8_t value);
	void SetMSControl(MSControl b, State st);

	/*
	 03h, 04h R - ButtHI Status Registers
	 UP | DOWN | CS6(DOWN) | CS5(POWER) | CS4(UP) | CS3(LEFT) | CS2(MIDDLE) | CS1(PROXIMITY)
	 CS14 | CS13 | CS12 | CS11 | CS10 | CS9 | CS8 | CS7(RIGHT)
	 */
private:
	static uint8_t st_03, st_04;
protected:
	void UpdateCS(uint8_t *status1 = 0, uint8_t *status2 = 0);
	uint16_t GetCS() const;
	State GetCS(CS b) const;

	/*
	 0Fh R-C - Group Status Registers
	 LID | MULT | RESET | - | UP | DOWN | TAP | PH
	 */
private:
	static uint8_t st_0F;
protected:
	void UpdateSlide(uint8_t *status = 0);
	uint8_t GetSlide() const;
	State GetSlide(Slide b) const;

	/*
	 06h R-C/RW - Slider PositiHI/Volumetric Data Registers
	 - | POS[6:0]

	 Determined by POS_VOL bit (20h)
	 */
	uint8_t GetSliPos();
	uint8_t GetVolData();
	uint8_t SetVolData(uint8_t);

	/*
	 10h~1Dh R - Sensor Delta Count Registers
	 10h   CS1   Proximity
	 11h   CS2   Middle
	 12h   CS3   Left
	 13h   CS4   Up
	 14h   CS5   Power
	 15h   CS6   Down
	 16h   CS7   Right
	 17h   CS8   Slide 7
	 18h   CS9   Slide 6
	 19h   CS10 Slide 5
	 1Ah   CS11 Slide 4
	 1Bh   CS12 Slide 3
	 1Ch   CS13 Slide 2
	 1Dh   CS14 Slide 1
	 */
protected:
	uint8_t GetSDelta(SDelta b);

	/*
	 20h RW - ConfiguratiHI Registers
	 TIMEOUT | POS_VOL | BLK_DIG_NOISE | BLK_ANA_NOISE | MAX_DUR_EN_B | RPT_EN_B | MAX_DUR_EN_G | RPT_EN_G
	 */
	bool GetTimeOutConfig();bool GetPosVolConfig();bool GetNoiseConfig(bool *th,
	bool *flag); //noise threshold, noise flag
	bool GetMaxDurCalConfig(bool *sg, bool *gp); //nHI grouped, grouped
	bool GetRptRateConfig(bool *sg, bool *gp); //nHI grouped, grouped

	void SetTimeOutConfig(State);
	void SetPosVolConfig(State);
	void SetNoiseConfig(State th, State flag); //noise threshold, noise flag
	void SetMaxDurCalConfig(State sg, State gp); //nHI grouped, grouped
	void SetRptRateConfig(State sg, State gp); //nHI grouped, grouped

	/*
	 23h, 24h RW - Group ConfiguratiHI Registers
	 RPT_RATE_PH[3:0] | M_PRESS[3:0]
	 MAX_DUR_G[3:0] | RPT_RATE_SL[3:0]
	 */
	void GetGroupConfig(uint8_t *rpt_ph = 0, uint8_t *m_press = 0,
			uint8_t *max_dur = 0, uint8_t *rpt_sl = 0);

	/*
	 27h, 28h RW - Interrupt Enable Registers
	 G_INT_EN | S7_INT_EN | S6_INT_EN | S5_INT_EN | S4_INT_EN | S3_INT_EN | S2_INT_EN | S1_INT_EN
	 GPIO8_INT_EN | GPIO7_INT_EN | GPIO6_INT_EN | GPIO5_INT_EN | GPIO4_INT_EN | GPIO3_INT_EN | GPIO2_INT_EN | GPIO1_INT_EN
	 */
private:
	static uint8_t st_27, st_28;
protected:
	void UpdateIntEn(uint8_t *status1 = 0, uint8_t *status2 = 0);
	uint16_t GetIntEn() const;
	State GetIntEn(IntEn b) const;
	void SetIntEn(uint8_t value);
	void SetIntEn(IntEn b, State st);

	/*
	 42h RW - Proximity CHItrol Registers
	 CS1_PROX | PROX_SUM | - | PROX_AVG[1:0] | PROX_D_SENSE[2:0]
	 */
	bool GetProxEN();bool GetProxSum();
	uint8_t GetProxAvg();
	uint8_t GetProxSen();

	void SetProxEN(State);
	void SetProxSum(State);
	void SetProxAvg(uint8_t);
	void SetProxSen(uint8_t);

	/*
	 26h, 46h RW - CalibratiHI Activate Registers
	 Group | CS7 | CS6 | CS5 | CS4 | CS3 | CS2 | CS1
	 - | CS14 | CS13 | CS12 | CS11 | CS10 | CS9 | CS8
	 */
	void SetCalAct(uint8_t);
	void SetGroupCalAct(uint8_t);

	/*
	 3Eh RW - Slider Velocity ConfiguratiHI Registers
	 ACC_INT_EN | MAX_INT[2:0] | SLIDE_TIME[1:0] | RPT_SCALE[1:0]
	 */
	void SetAccelEN(State);
	void SetIntNum(uint8_t);
	void SetSliTime(uint8_t);
	void SetRptScale(uint8_t);

	/*
	 70h RW - LED/GPIO DirectiHI Register
	 LED8_DIR | LED7_DIR | LED6_DIR | LED5_DIR | LED4_DIRS4 | LED3_DIR | LED2_DIRS2 | LED1_DIR1
	 */
protected:
	uint8_t GetGPIODir();
	State GetGPIODir(GPIODir b);
	void SetGPIODir(uint8_t value);
	void SetGPIODir(GPIODir b, State st);

	/*
	 80h RW - Sensor LED Linking Registers
	 Group | CS7 | CS6 | CS5 | CS4 | CS3 | CS2 | CS1
	 */
protected:
	State GetLEDLinking(LEDLinking b);
	void SetLEDLinking(uint8_t value);
	void SetLEDLinking(LEDLinking b, State st);
};

uint8_t CAP1114_Driver::st_00 = 0, CAP1114_Driver::st_03 = 0, CAP1114_Driver::st_04 = 0;
uint8_t CAP1114_Driver::st_73 = 0, CAP1114_Driver::st_74 = 0, CAP1114_Driver::st_0F = 0;
uint8_t CAP1114_Driver::st_27 = 0, CAP1114_Driver::st_28 = 0;

CAP1114_Driver::CAP1114_Driver() : I2CSensor(0x28) {
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// allow multiple touches
	WriteRegister(CAP1114_MTBLK, 0);
	/*WriteRegBit(CAP1114_MAIN, B1, HI);          //HI LED11
	 WriteRegBit(CAP1114_MAIN, B5, LO);
	 WriteRegBit(CAP1114_MAIN, B4, LO);*/
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}

CAP1114_Driver::~CAP1114_Driver() {
}

}
#endif
