/*
Provided to you by Emlid Ltd (c) 2014.
twitter.com/emlidtech || www.emlid.com || info@emlid.com

Example: Control servos connected to PCA9685 driver onboard of Navio shield for Raspberry Pi.

Connect servo to Navio's rc output and watch it work.
Output 1 on board is connected to PCA9685 channel 3, output 2 to channel 4 and so on.
To use full range of your servo correct SERVO_MIN and SERVO_MAX according to it's specification.

To run this example navigate to the directory containing it and run following commands:
make
./Servo
*/

#define NAVIO_RCOUTPUT_1 3
#define NAVIO_RCOUTPUT_2 4
#define NAVIO_RCOUTPUT_3 5
#define NAVIO_RCOUTPUT_4 6

#define SERVO_MIN 1.290 /*mS*/
#define SERVO_MAX 1.800 /*mS*/

#include "gpio.h"
#include "PCA9685.h"
#include <iostream>
#include "SDL2/SDL.h"
using namespace Navio;
using namespace std;

int main()
{
//  stuff needed to run the SDL and the drone files
// ---------------------------------------------------------------------------------
    static const uint8_t outputEnablePin = RPI_GPIO_27;

    Pin pin(outputEnablePin);

    if (pin.init()) {
        pin.setMode(Pin::GpioModeOutput);
        pin.write(0); /* drive Output Enable low */
    } else {
        fprintf(stderr, "Output Enable not set. Are you root?");
    }

    PCA9685 pwm;

    pwm.initialize();
    pwm.setFrequency(50);

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
	printf("Unable to initialize SDL: %s\n", SDL_GetError());
	return 1;
    }



//---------------------------------------------------------------------------------

//==================================================================================
// sets all the motors to 1.290 ms

       pwm.setPWMmS(NAVIO_RCOUTPUT_1, 1.290);
       pwm.setPWMmS(NAVIO_RCOUTPUT_2, 1.290);
       pwm.setPWMmS(NAVIO_RCOUTPUT_3, 1.290);
       pwm.setPWMmS(NAVIO_RCOUTPUT_4, 1.290);
	cout << "Armed!!!" << endl;
    sleep(2);
//===================================================================================  


    double motor1 = 1.330;
    double motor2 = 1.330;
    double motor3 = 1.330;
    double motor4 = 1.330;
    double allMotors = 1.330;
 //   int x = 1;

    double test = 0.1;
  

	SDL_Event event;
       int running = 1;
 
        while(running == 1) {
        while (SDL_PollEvent( &event ) != 0){
 	if(event.type == SDL_QUIT){
	running = 0;

	} else if(event.type == SDL_KEYDOWN){
	
	switch(event.key.keysym.sym){

		case SDLK_UP:
		cout << "space was pressed" << endl;
		motor1 += .01;
		motor2 += .02;
		motor3 += .01;
		motor4 += .01;
		allMotors += .01;
		break;
		
		case SDLK_DOWN:
		motor1 -= .01;
		motor2 -= .02;
		motor3 -= .01;
		motor4 -= .01;
		cout << "the 1 key was pressed" << endl;
		allMotors -= .01;
		break;

		case SDLK_w:
                motor2 += .02;
		motor3 += .01;
                cout << "the 2 key was pressed" << endl;
                break;

		case SDLK_s:
                motor1 += .01;
                motor4 += .01;
                cout << "the 2 key was pressed" << endl;
		break;
		
		case SDLK_d:
		motor3 += .01;
                motor4 += .01;
                cout << "the 2 key was pressed" << endl;
		break;

		case SDLK_a:
                motor1 += .01;
                motor2 += .01;
                cout << "the 2 key was pressed" << endl;
		break;
		
		case SDLK_q:
		allMotors = 1.220;
		motor1 = allMotors;
		motor2 = allMotors;
		motor3 = allMotors;
		motor4 = allMotors;
		cout << "q was pressed" << endl;
		running = 0;


	}}else if(event.type == SDL_KEYUP){
		switch(event.key.keysym.sym){

                case SDLK_w:
                motor2 = allMotors;
                motor3 = allMotors;
                cout << "the 2 key was pressed" << endl;
                break;

                case SDLK_s:
                motor1 = allMotors;
                motor4 = allMotors;
                cout << "the 2 key was pressed" << endl;
                break;
                
                case SDLK_d:
                motor3 = allMotors;
                motor4 = allMotors;
                cout << "the 2 key was pressed" << endl;
                break;

                case SDLK_a:
                motor1 = allMotors;
                motor2 = allMotors;
                cout << "the 2 key was pressed" << endl;
                break;



		}}
	

	cout << "out of switch" << endl;
	cout << "motorspeed is " << motor1 << " " << motor2 << " " << motor3 << " " << motor4 << endl;
//        cout << "pwm is " << x << endl;
	pwm.setPWMmS(NAVIO_RCOUTPUT_1, motor1);
        pwm.setPWMmS(NAVIO_RCOUTPUT_2, motor2);
        pwm.setPWMmS(NAVIO_RCOUTPUT_3, motor3);
        pwm.setPWMmS(NAVIO_RCOUTPUT_4, motor4);
/*	if (motor1 <= 1.210){
		pwm.setFrequency(0);
		cout << "exiting program" << endl;
		break;
	    }else{
		continue;
		} */
		} 
	if(allMotors <= 1.250){
		cout << "exiting" << endl;		
		break;
		}
     }

    return 0;
}

