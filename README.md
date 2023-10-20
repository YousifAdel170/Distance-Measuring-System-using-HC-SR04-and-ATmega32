# measure-distance-using-ultrasonic-sensor
system to measure the distance using ultrasonic sensor


⚙️🖥️ Hardware Setup: For this project, I utilized the mighty ATmega32 MCU, operating at a clock frequency of 8 MHz.
The system that measure the distance according to the readings from the Ultrasonic sensor.


📏System Of measure the distance according to the ultrasonic sensor: 
The system's primary role is to display the distance on the LCD screen according the readings from the ultrasonic sensor

🔗Ultrasonic Sensor:
  The module has only 4 pins, Vcc , Gnd, Trig, and Echo.
 📏 VCC - +5 V supply
 📏 TRIG – Trigger input of sensor. Microcontroller applies 10 us trigger pulse to the HC-SR04 ultrasonic module.
 📏 ECHO–Echo output of sensor. Microcontroller reads/monitors this pin to detect the obstacle or to find the distance.
 📏 GND – Ground
  
    Total distance is divided by 2 because signal travels from HC-SR04 to object and returns to the module HC-SR-04.
  
    To calculate the distance:  total distance = (340*Time of High(raising + falling)) / 2

💻 System Output: Using a display with an LCD (4x16) and the 8-bit mode, the current status of the ultrasonic is continuously updated and presented.

🔌 Hardware Components: The system makes use of many important hardware elements to accomplish this functionality: 
  ▪ LCD 4x16 is used to display the distance that measured using Ultrasonic sensor🖥️ 
  ▪ The Ultrasonic Sensor, which delivers accurate distance readings ☄

🏗️ Layered Architecture: 

▪ Application Layer: The Adjust the distance using is handled by this layer, which also decides what is displayed on the LCD according to the distance readings. 

▪ HAL (Hardware Abstraction Layer): The HAL acts as an interface between the application layer and the hardware components. 
  It encompasses modules for the LCD, Ultrasonic Sensor. It handles initialization, configuration, and communication with these hardware modules. 

▪ MCAL (Microcontroller Abstraction Layer): The MCAL interacts directly with the microcontroller's hardware peripherals. 
  1) It includes modules for GPIO (General Purpose Input/Output) to control various pins.
  2) ICU (Input Capture Unit) for reading distance values from the ultrasonic sensor.



