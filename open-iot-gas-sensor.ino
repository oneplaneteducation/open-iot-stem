#include <lib.h>

/**
 * @file RAK12004_MQ2_SmokeDetection.ino
 * @author rakwireless.com
 * @brief use MQ2 to detect smoke and use RAK1801 buzzer alarm
 * @version 0.1
 * @date 2021-05-08
 * @copyright Copyright (c) 2021
 */
#include <Wire.h>
#include "ADC121C021.h"
#include <U8g2lib.h> // Click to install library: http://librarymanager/All#u8g2

#define BUZZER_CONTROL WB_IO1
//Slot A: WB_IO1 17
//Slot B: WB_IO2 34
//Slot C: WB_IO3 21
//Slot D: WB_IO5 9

#if defined(_VARIANT_RAK4630_)
  #define PWM_FOSC 16000000 //
#elif defined(_VARIANT_RAK11300_) 
#else 
   // use first channel of 16 channels (started from zero)
  #define LEDC_CHANNEL_0  0
  // use 13 bit precission for LEDC timer
  #define LEDC_TIMER_13_BIT  13
  // use 4000 Hz as a LEDC base frequency
  #define LEDC_BASE_FREQ     4000               
#endif

#define EN_PIN WB_IO6	 //Logic high enables the device. Logic low disables the device
#define ALERT_PIN WB_IO5 //a high indicates that the respective limit has been violated.
#define MQ2_ADDRESS 0x51 //the device i2c address

#define RatioMQ2CleanAir (1.0) //RS / R0 = 1.0 ppm
#define MQ2_RL (10.0)		   //the board RL = 10KΩ  can adjust

ADC121C021 MQ2;
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);

uint16_t result;
char displayData[32]; //OLED dispaly datas

//Function declaration
void firstDisplay();
void buzzer_init();
void buzzer(unsigned long freq);
void stop_buzzer();
void setup()
{
	pinMode(ALERT_PIN, INPUT);
	pinMode(EN_PIN, OUTPUT);
	digitalWrite(EN_PIN, HIGH); //power on RAK12004
	delay(500);
	time_t timeout = millis();
	Serial.begin(115200);
	while (!Serial)
	{
		if ((millis() - timeout) < 5000)
		{
			delay(100);
		}
		else
		{
			break;
		}
	}
  buzzer_init();
	//***********OLED display init *****************************************
	u8g2.begin();
	u8g2.clearDisplay();
	u8g2.clearBuffer();
	u8g2.setFont(u8g2_font_ncenB10_tr); // choose a suitable font
	memset(displayData, 0, sizeof(displayData));
	sprintf(displayData, "RAK12004 Test");
	u8g2.drawStr(3, 15, displayData);
	sprintf(displayData, "MQ2 checking...");
	u8g2.drawStr(3, 45, displayData);
	u8g2.sendBuffer();

	//********ADC121C021 ADC convert init ********************************
	while (!(MQ2.begin(MQ2_ADDRESS, Wire)))
	{
		Serial.println("please check device!!!");
		delay(200);
	}
	Serial.println("RAK12004 test Example");

	//**************init MQ2 *****************************************************
	MQ2.setRL(MQ2_RL);
	MQ2.setA(-0.98);			//A -> Slope, -0.689
	MQ2.setB(1.154);			//B -> Intersect with X - Axis  1.154
								//Set math model to calculate the PPM concentration and the value of constants
	MQ2.setRegressionMethod(0); //PPM =  pow(10, (log10(ratio)-B)/A)

	float calcR0 = 0;
	for (int i = 1; i <= 100; i++)
	{
		calcR0 += MQ2.calibrateR0(RatioMQ2CleanAir);
	}
	MQ2.setR0(calcR0 / 10);
	if (isinf(calcR0))
	{
		Serial.println("Warning: Conection issue founded, R0 is infite (Open circuit detected) please check your wiring and supply");
		while (1)
			;
	}
	if (calcR0 == 0)
	{
		Serial.println("Warning: Conection issue founded, R0 is zero (Analog pin with short circuit to ground) please check your wiring and supply");
		while (1)
			;
	}

	float r0 = MQ2.getR0();
	Serial.printf("R0 Value is:%3.2f\r\n", r0);
	firstDisplay();
	delay(3000);
}
void loop()
{
	float sensorPPM;
	float PPMpercentage;

	Serial.println("Getting Conversion Readings from ADC121C021");
	Serial.println(" ");
	sensorPPM = MQ2.readSensor();
	Serial.printf("sensor PPM Value is: %3.2f\r\n", sensorPPM);
	PPMpercentage = sensorPPM / 10000;
	Serial.printf("PPM percentage Value is:%3.2f%%\r\n", PPMpercentage);
	Serial.println(" ");
	Serial.println("        ***************************        ");
	Serial.println(" ");

	u8g2.clearDisplay();
	u8g2.clearBuffer();
	u8g2.setFont(u8g2_font_ncenB10_tr); // choose a suitable font
	memset(displayData, 0, sizeof(displayData));
	sprintf(displayData, "RAK12004 Test");
	u8g2.drawStr(3, 15, displayData);

	sprintf(displayData, "Propane:");
	u8g2.drawStr(3, 30, displayData);

	sprintf(displayData, "%3.2f PPM", sensorPPM);
	u8g2.drawStr(3, 45, displayData);

	sprintf(displayData, "%3.2f %%", PPMpercentage);
	u8g2.drawStr(3, 60, displayData);
	u8g2.sendBuffer();

	if (sensorPPM > 3000)
	{
		buzzer(4000); //4KHz
		Serial.println("value over AlertHighThreshold !!!");
	}
	else
	{
		stop_buzzer();
	}
	delay(1000);
}
void firstDisplay()
{
	u8g2.clearDisplay();
	u8g2.clearBuffer();
	u8g2.setFont(u8g2_font_ncenB10_tr); // choose a suitable font
	memset(displayData, 0, sizeof(displayData));
	sprintf(displayData, "RAK12004 Test");
	u8g2.drawStr(3, 15, displayData);
	u8g2.sendBuffer();

	sprintf(displayData, "R0:%3.3f", MQ2.getR0());
	u8g2.drawStr(3, 30, displayData);
	u8g2.sendBuffer();

	float voltage = MQ2.getSensorVoltage();
	sprintf(displayData, "voltage:%3.3f", voltage);
	u8g2.drawStr(3, 45, displayData);
	u8g2.sendBuffer();
}
void buzzer_init()
{
  #if defined(_VARIANT_RAK4630_)
    #define BOARD "RAK4631 "
    pinMode(BUZZER_CONTROL, OUTPUT);
    HwPWM0.addPin(BUZZER_CONTROL);
    //  HwPWM0.setResolution(4); // set max value by 2^bitnum - 1
    //  HwPWM0.setMaxValue(4000-1);   // set max value = 16000000/pwm_frequency - 1
    buzzer(4000); //4000Hz
    HwPWM0.stop();
  #elif defined(_VARIANT_RAK11300_) 
    #define BOARD "RAK11300"
  //  tone(BUZZER_CONTROL,4000,2000); 
  #else 
    #define BOARD "RAK11200" 
    ledcSetup(LEDC_CHANNEL_0, LEDC_BASE_FREQ, LEDC_TIMER_13_BIT); // Set channel 0  
    ledcAttachPin(BUZZER_CONTROL, LEDC_CHANNEL_0);                
  #endif
  Serial.println(BOARD); 
}
void buzzer(unsigned long freq)
{
  #if defined(_VARIANT_RAK4630_)
    unsigned long duty = 0;
    unsigned long pwm_period = 0;
    pwm_period = PWM_FOSC / freq - 1;
    duty = PWM_FOSC / freq / 2;
    HwPWM0.setMaxValue(pwm_period); // set max value = 16000000/pwm_frequency - 1
    HwPWM0.writePin(BUZZER_CONTROL, duty, false);
  #elif defined(_VARIANT_RAK11300_) 
    tone(BUZZER_CONTROL,freq,freq/2);
  #else 
    // calculate duty, 8191 from 2 ^ 13 - 1
    uint32_t duty = (8191 / 2);
    // write duty to LEDC
    ledcWrite(LEDC_CHANNEL_0, duty);          
  #endif
}

void stop_buzzer()
{
  #if defined(_VARIANT_RAK4630_)
    HwPWM0.stop();
  #elif defined(_VARIANT_RAK11300_) 
    noTone(BUZZER_CONTROL);
  #else 
    ledcWrite(LEDC_CHANNEL_0, 0);   
  #endif
}