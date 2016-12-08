#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, I2C_1,  liftLeft,       sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  liftRight,      sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           rightbacktopmost, tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           leftMiddle,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           leftBack,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           liftRightTop,  tmotorVex393_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port5,           liftLeftTop,   tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port6,           leftBackTop,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           rightBackTop,  tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           rightBack,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           leftbacktopmost, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          rightFront,    tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX2)
#pragma competitionControl(Competition)
#include "Vex_Competition_Includes.c"

#include "functions.c"
#include "gyrolib.c"
#include "pid.c"

void pre_auton() {
	bStopTasksBetweenModes = true;
	SensorValue[leftEncoder] = SensorValue[rightEncoder] = 0;
	//Completely clear out any previous sensor readings by setting the port to "sensorNone"
	SensorType[in1] = sensorNone;
	wait1Msec(1000);
	//Reconfigure Analog Port 1 as a Gyro sensor and allow time for ROBOTC to calibrate it
	SensorType[in1] = sensorGyro;
	wait1Msec(2000);
	SensorFullCount[in1] = 7200;

	SensorScale[in1] = 100;
	//GyroInit();
}

task autonomous() {

	driveKp = 0.3;
	driveKi = 0.05;
	driveKd = 0.0;
	stopTask(drivePID);

	//go(10);
	//wait1Msec(1500);
	//go(-10);
	//wait1Msec(1500);
	//go(90);
	//wait1Msec(1500);
	//go(-10);
	//wait1Msec(1500);
	//go(90);
	//wait1Msec(1500);
	//go(-30);
	//wait1Msec(1500);
	//go(30);
	//wait1Msec(1500);
	//go(-30);
	//wait1Msec(1500);

	///////////////////////////////////
	// this kinda works
	go(20);								// go forward
	wait1Msec(1000);
	stopTask(drivePID);

	startGyroTasks();
	targetGyro = 3150;		// turn 45 degrees to face pole
	wait1Msec(3000);

	go(-22);							// drive backwards
	wait1Msec(3000);
	stopTask(drivePID);

	targetGyro = 6750;		// do 360 turn
	wait1Msec(3500);
	//stopTask(gyroTurn);

	//go(-5);
	//wait1Msec(1000);
	//stopTask(drivePID);

	targetGyro = 7200; 		// realign with pole
	wait1Msec(500);
	stopGyroTasks();

	go(-25);							// drive backwards
	wait1Msec(1500);
	stopTask(drivePID);


	lift(127);
	wait1Msec(5000);
	lift(-127);
	wait1Msec(6200);
	lift(0);

	// This doesnt work at all
	//go(24);
	//wait1Msec(1500);
	//stopTask(drivePID);

	//startGyroTasks();
	//targetGyro = 900;
	//wait1Msec(1500);
	//stopGyroTasks();

	//go(-5);
	//wait1Msec(500);
	//stopTask(drivePID);

	//targetGyro = 3150;
	//wait1Msec(1500);
	//stopGyroTasks();


}

task usercontrol() {
	float x;

	while (true) {
		x = getMotorEncoder(liftLeftTop);
		arcadeDrive();
		liftControl();
		lcd();
	}
}
