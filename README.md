# ESP 32 PWM Fan controller

This arduino code is used for a project to control a computer fan by sending a PWM signal. The speed can be controlled
by reading a potentiometer value. The original code was meant to control 3 LED's with PWM but a tweaked it to control the fan.

> Images are inside the `img` folder (exluded from the github repo )

The ESP32 can handle 3 PWM output signals. For this project only one is used.

- A 24 V DC power supply is used to power the Noctua computer fan. The voltage is further reduced ( to 5 V )to power the ESP32 circuit.
- 5Kohm potentiometer to control the fan speed
- Noctua 24V Industrial PPC fan

## AI explanation of the code

This Arduino code is designed to control the brightness of three LEDs (red, green, and blue) using Pulse Width Modulation (PWM) based on analog inputs from three potentiometers (or other analog sensors). Here’s a detailed breakdown:

1. Pin and Variable Definitions

```ccp
const int redLEDPin = 16; /_ GPIO16 _/
const int greenLEDPin = 17; /_ GPIO17 _/
const int blueLEDPin = 4; /_ GPIO4 _/
```

These lines define the GPIO pins to which the red, green, and blue LEDs are connected.

```ccp
uint16_t redDutyCycle;
uint16_t greenDutyCycle;
uint16_t blueDutyCycle;
```

These variables store the duty cycle values for each LED, which determine their brightness.

```ccp
const int redPWMFreq = 25000; /_ 25 KHz _/
const int redPWMChannel = 0;
const int redPWMResolution = 8;
const int RED_MAX_DUTY_CYCLE = (int)(pow(2, redPWMResolution) - 1);
```

For the red LED:

```ccp
redPWMFreq: PWM frequency (25 kHz).
redPWMChannel: PWM channel (0).
redPWMResolution: PWM resolution (8 bits, so max duty cycle is 255).
RED_MAX_DUTY_CYCLE: Maximum possible duty cycle for red LED.
```

Similar definitions exist for green and blue LEDs, with different frequencies and resolutions.

```ccp
const int ADC*RESOLUTION = 4095; /* 12-bit \_/
```

The ESP32’s ADC (Analog to Digital Converter) has a 12-bit resolution, so the maximum value is 4095.

2. Setup Function

```ccp
void setup() {
Serial.begin(115200);
ledcSetup(redPWMChannel, redPWMFreq, redPWMResolution);
ledcSetup(greenPWMChannel, greenPWMFreq, greenPWMResolution);
ledcSetup(bluePWMChannel, bluePWMFreq, bluePWMResolution);

ledcAttachPin(redLEDPin, redPWMChannel);
ledcAttachPin(greenLEDPin, greenPWMChannel);
ledcAttachPin(blueLEDPin, bluePWMChannel);
}

Serial.begin(115200); initializes serial communication for debugging.
ledcSetup() configures each PWM channel with its frequency and resolution.
ledcAttachPin() attaches each LED pin to its corresponding PWM channel.
```

3. Loop Function

```ccp
void loop() {
redDutyCycle = analogRead(A0);
greenDutyCycle = analogRead(A3);
blueDutyCycle = analogRead(A4);

redDutyCycle = map(redDutyCycle, 0, ADC_RESOLUTION, 0, RED_MAX_DUTY_CYCLE);
greenDutyCycle = map(greenDutyCycle, 0, ADC_RESOLUTION, 0, GREEN_MAX_DUTY_CYCLE);
blueDutyCycle = map(blueDutyCycle, 0, ADC_RESOLUTION, 0, BLUE_MAX_DUTY_CYCLE);

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
```

Reading Analog Inputs:

```ccp
analogRead(A0), analogRead(A3), analogRead(A4) read the values from three analog inputs (potentiometers or sensors).
```

Mapping Values:

map() scales the 12-bit ADC value (0–4095) to the maximum duty cycle for each LED (e.g., 0–255 for red, 0–8191 for green, etc.).

Setting PWM Outputs:

ledcWrite() sets the duty cycle for each LED, controlling its brightness.

Serial Output:

Prints the current duty cycle values for debugging.

Delay:

delay(1000) pauses for 1 second before repeating the loop.

Summary

This code reads analog values from three inputs (A0, A3, A4), maps them to PWM duty cycles, and controls the brightness of three LEDs (red, green, blue) accordingly.
The use of different PWM frequencies and resolutions for each LED is unusual and may be for specific hardware requirements or to avoid interference.
The serial output helps monitor the duty cycle values in real time.
If you have any questions about specific parts or want to modify the code, let me know!

## Wire diagram

Here’s a simple wiring diagram for connecting the ESP32 to three LEDs (red, green, blue) and three potentiometers (or analog sensors) based on your code:

Components Needed

ESP32 board
3x LEDs (red, green, blue)
3x 220Ω resistors (for LEDs)
3x 10kΩ potentiometers (or analog sensors)
Breadboard and jumper wires

Wiring Diagram (Textual Description)

1. LED Connections

Red LED:

Anode (long leg) → GPIO16 (via 220Ω resistor)
Cathode (short leg) → GND

Green LED:

Anode → GPIO17 (via 220Ω resistor)
Cathode → GND

Blue LED:

Anode → GPIO4 (via 220Ω resistor)
Cathode → GND

2. Potentiometer Connections

Potentiometer 1 (for Red LED):

Outer pins: 3.3V and GND
Middle pin (wiper) → ADC1_CH0 (GPIO36, labeled A0 on some boards)

Potentiometer 2 (for Green LED):

Outer pins: 3.3V and GND
Middle pin → ADC1_CH3 (GPIO39, labeled A3 on some boards)

Potentiometer 3 (for Blue LED):

Outer pins: 3.3V and GND
Middle pin → ADC1_CH4 (GPIO32, labeled A4 on some boards)

Visual Representation

ESP32
┌───────────────────────┐
│ │
│ 3.3V ────┬───────────┤
│ │ │
│ GPIO16───┴───[220Ω]───[Red LED]───GND
│ │
│ GPIO17───┴───[220Ω]───[Green LED]───GND
│ │
│ GPIO4────┴───[220Ω]───[Blue LED]───GND
│ │
│ GPIO36 (A0)───┬───────┤
│ │ │
│ GPIO39 (A3)───┼───[10kΩ Potentiometers]───3.3V & GND
│ │ │
│ GPIO32 (A4)───┴───────┤
│ │
└───────────────────────┘

### Notes

ESP32 ADC Pins: On most ESP32 boards, ADC1_CH0 is GPIO36, ADC1_CH3 is GPIO39, and ADC1_CH4 is GPIO32. Double-check your board’s pinout.
Resistors: Always use a current-limiting resistor (e.g., 220Ω) in series with LEDs to prevent damage.
Potentiometers: Connect the outer pins to 3.3V and GND, and the middle pin to the ADC input.
