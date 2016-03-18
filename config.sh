#!/bin/bash
cd /home/pi/drone
g++ -o Servo Servo.cpp gpio.cpp PCA9685.cpp I2Cdev.cpp  `sdl2-config --cflags --libs`

