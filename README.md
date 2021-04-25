# Smart-Car-using-Arduino
Using arduino to make an automatic car with road cleaning, temperature based Air Conditioner, Light Sensitive Head lights and humidity and temperature display

## Circuit Diagram

![Accessory System Circuit Diagram](https://github.com/aaryan2134/Smart-Car-using-Arduino/blob/b8e2b2f830e75f8fa81f20f0c0def755622ff1a8/circuit%20diagram%202.png)
![Driving System Circuit Diagram](circuit%20diagram%201.png)

## Requirements
Ultrasonic sensor, a chassis, 2 dc motors, L293D motor driver IC, led (optional), buzzer (optional), LDR(for the headlights), some jumper wires, batteries and the Arduino Uno R3
This robot is Arduino Atmega 328p based. The robot has an ultrasonic sensor functioning as its “eyes”. It has been fixed to a servo so that the range of the sensor can be enhanced. 
Whenever it detects an object, it stops and scans the area. Then it takes the path with the maximum place for its movement. The Arduino Uno R3 acts as its brain. The motors are controlled according to distance from the object detected. The maximum range of the sensor is 400-500cm.
**Note: **Download the libraries to run the codes

## Various Parts of the project
1. **Autonomous Travel: **The 

## Future Improvements
The Ultrasonic sensor can be upgraded with cameras and a more powerful brain and then can be used in automatic cars. 
Even Navigation systems can be used to control the car.
Also, rather than using a brush, a vacuum based cleaning mechanism can be used. Even solar panels can be added for further improvements.

## Schematic Diagram
![Accessory System Circuit Diagram](circuit%20diagram%203.png)
![Driving System Circuit Diagram](circuit%20diagram%204.png)

## Initial Testing Phase
![Test 1](Initial%20Testing%202.jpg)
![Test 2](Initial%20Testing.jpg)


[Prototype Video Link](https://youtu.be/BLX8ju8Vj1I)
