#include <Arduino.h>

const int redLEDPin = 16;  /* GPIO16 */
const int greenLEDPin = 17;  /* GPIO17 */
const int blueLEDPin = 4;  /* GPIO4 */
uint16_t redDutyCycle;
uint16_t greenDutyCycle;
uint16_t blueDutyCycle;
const int redPWMFreq = 25000; /* 25 KHz */
const int redPWMChannel = 0;
const int redPWMResolution = 8;
const int RED_MAX_DUTY_CYCLE = (int)(pow(2, redPWMResolution) - 1);
const int greenPWMFreq = 8000; /* 8 KHz */
const int greenPWMChannel = 2;
const int greenPWMResolution = 13;
const int GREEN_MAX_DUTY_CYCLE = (int)(pow(2, greenPWMResolution) - 1);
const int bluePWMFreq = 10000; /* 10 KHz */
const int bluePWMChannel = 4;
const int bluePWMResolution = 14;
const int BLUE_MAX_DUTY_CYCLE = (int)(pow(2, bluePWMResolution) - 1);
const int ADC_RESOLUTION = 4095; /* 12-bit */
// use 4 bit precission for LEDC timer
#define LEDC_TIMER_4_BIT  4

// use 2.7MHz Hz as a LEDC base frequency
#define LEDC_BASE_FREQ     2700000
#define LED_PIN            5
void setup()
{  
/* Initialize Serial Port */
  Serial.begin(115200);
/* Initialize PWM Channels with Frequency and Resolution */
ledcSetup(redPWMChannel, redPWMFreq, redPWMResolution);
// ledcSetup(redPWMChannel, LEDC_BASE_FREQ, LEDC_TIMER_4_BIT);
ledcSetup(greenPWMChannel, greenPWMFreq, greenPWMResolution);
ledcSetup(bluePWMChannel, bluePWMFreq, bluePWMResolution);
/* Attach the LED PWM Channel to the GPIO Pin */
ledcAttachPin(redLEDPin, redPWMChannel);
ledcAttachPin(greenLEDPin, greenPWMChannel);
ledcAttachPin(blueLEDPin, bluePWMChannel);
}
void loop()
{
/* Read Analog Input from three ADC Inputs */
  redDutyCycle = analogRead(A0);
  greenDutyCycle = analogRead(A3);
  blueDutyCycle = analogRead(A4); 
/* Map ADC Output to maximum possible dutycycle */
  redDutyCycle = map(redDutyCycle, 0, ADC_RESOLUTION, 0, RED_MAX_DUTY_CYCLE);
  greenDutyCycle = map(greenDutyCycle, 0, ADC_RESOLUTION, 0, GREEN_MAX_DUTY_CYCLE);
  blueDutyCycle = map(blueDutyCycle, 0, ADC_RESOLUTION, 0, BLUE_MAX_DUTY_CYCLE);
/* Set PWM Output of Channel with desired dutycycle */ 
ledcWrite(redPWMChannel, redDutyCycle);
ledcWrite(greenPWMChannel, greenDutyCycle);
ledcWrite(bluePWMChannel, blueDutyCycle);
  Serial.println("RED -- GREEN -- BLUE");
  Serial.print(redDutyCycle);
  Serial.print(" -- ");
  Serial.print(greenDutyCycle);
  Serial.print(" -- ");
  Serial.print(blueDutyCycle);
  Serial.print("\n");
delay(1000);
}