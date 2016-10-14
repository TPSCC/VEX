#pragma config(Sensor, dgtl1,  Pneumatic1,     sensorDigitalOut)
#pragma config(Sensor, dgtl2,  Pneumatic2,     sensorDigitalOut)
#pragma config(Motor,  port1,           leftFront,     tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           leftBack,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           rightBack,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          rightFront,    tmotorVex393_HBridge, openLoop)
#pragma platform(VEX2)
#pragma competitionControl(Competition)

#include "Vex_Competition_Includes.c"

void setLeft(int speed) {
    motor[leftFront] = speed;
    motor[leftBack] = speed;
}

void setRight(int speed) {
    motor[rightFront] = speed;
    motor[rightBack] = speed;
}

void setAll(int speed) {
    setLeft(speed);
    setRight(speed);
}

void forward (int time, int mspeed){
	playSound(soundFastUpwardTones);
    setAll(-mspeed);
    delay(time);
    setAll(0);
}

void turnl (int time, int dif) { 
	playSound(soundBlip);
    setLeft(-127 - dif);
    setRight(-127);
    delay(time);
    setAll(0);
}

void turnr (int time, int dif) {
    playSound(soundBeepBeep);
    setRight(-127 + dif);
    setLeft(-127);
    delay(time);
    setAll(0);
}

void pre_auton(){
	bStopTasksBetweenModes = true;
}
//to turn left use a 0 and to turn right use a 1
task autonomous(){
	forward(1000, 127); //calling the drive forward function with a time of 1000 and a speed of 127
	turnl(1000, 50); //turning left with a diff of speed of 45
}

task usercontrol(){
	int X2 = 0, Y1 = 0, X1 = 0, threshold = 15;
	while(true){
		//Create deadzone for Y1/Ch3
		if(abs(vexRT[Ch3]) > threshold)
			Y1 = vexRT[Ch3];
		else
			Y1 = 0;
		//Create deadzone for X1/Ch4
		if(abs(vexRT[Ch4]) > threshold)
			X1 = vexRT[Ch4];
		else
			X1 = 0;
		//Create deadzone for X2/Ch1
		if(abs(vexRT[Ch1]) > threshold)
			X2 = vexRT[Ch1];
		else
			X2 = 0;
			//Remote Control Commands
		motor[frontRight] = Y1 - X2 - X1;
		motor[backRight] =  Y1 - X2 + X1;
		motor[frontLeft] = Y1 + X2 + X1;
		motor[backLeft] =  Y1 + X2 - X1;
	}
}
