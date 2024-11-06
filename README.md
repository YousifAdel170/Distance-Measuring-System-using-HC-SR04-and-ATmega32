# Distance Measuring System using HC-SR04 and ATmega32
This project implements a distance measurement system using the HC-SR04 Ultrasonic Sensor and ATmega32 Microcontroller. 
The measured distance is displayed on a 4x16 LCD. The system is designed with a layered architecture that includes drivers for GPIO, ICU, LCD, and Ultrasonic Sensor.

## Features

### Ultrasonic Distance Measurement:
Uses the HC-SR04 Ultrasonic Sensor to measure distances in centimeters.

### LCD Display:
Displays the measured distance on a 4x16 LCD.

### ATmega32 Microcontroller:
Runs the system at a clock frequency of 8 MHz.

### Layered Architecture:
The project is implemented using a modular design with separate drivers for each component.

## System Architecture
The system is organized based on a layered architecture model and includes the following drivers:

### GPIO Driver:
Controls the input and output pins, including those for the LCD and the ultrasonic sensor.

### ICU Driver:
Handles the timing for ultrasonic sensor readings using the Input Capture Unit.

### LCD Driver:
Manages communication with the 4x16 LCD.

### Ultrasonic Sensor Driver:
Controls the HC-SR04 sensor to trigger pulses and measure the echo time to calculate distance.

## Components

### ATmega32 Microcontroller

### HC-SR04 Ultrasonic Sensor

### 4x16 LCD

### GPIO Pins

### ICU for pulse detection

## How It Works

### 1. The HC-SR04 Ultrasonic Sensor is triggered by sending a pulse to the Trigger Pin.

### 2. The sensor sends out a sound pulse and waits for the echo to return. The time taken for the echo to return is measured using the Input Capture Unit (ICU) of the ATmega32.

### 3. The time duration is used to calculate the distance.

### 4. The calculated distance is displayed on the 4x16 LCD.

## Functions

### The Ultrasonic Driver contains the following functions:

#### Ultrasonic_init():

##### Initializes the ICU and sets up the trigger pin.

#### Ultrasonic_Trigger():

##### Sends a trigger pulse to the HC-SR04 sensor.

#### Ultrasonic_readDistance():

##### Sends the trigger pulse and reads the distance using the ICU.

#### Ultrasonic_edgeProcessing():

##### Callback function called by the ICU to process the echo and calculate the pulse width.

## Requirements

### ATmega32 Microcontroller

### HC-SR04 Ultrasonic Sensor

### 4x16 LCD

### C programming language for the firmware

## License

### This project is open-source
