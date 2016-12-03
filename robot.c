#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, I2C_1,  liftRight,      sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  liftLeft,       sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           leftFront,     tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           leftMiddle,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           leftBack,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           liftRightTop,  tmotorVex393_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port5,           liftLeftTop,   tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port6,           leftBackTop,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           rightBackTop,  tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           rightBack,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           rightMiddle,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          rightFront,    tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX2)
#pragma competitionControl(Competition)
#include "Vex_Competition_Includes.c"

#include "functions.c"
#include "pid.c"

void pre_auton() {
	bStopTasksBetweenModes = true;
  SensorScale[gyro] = 900/669;
  wait1Msec(2000);
	SensorValue[leftEncoder] = SensorValue[rightEncoder] = 0;
}
//pls work
task autonomous() {
	driveKp = 0.3;
	driveKi = 0.05;
	driveKd = 0.0;

	kpGyro = 0.05;
	kiGyro = 0.06;
	kdGyro = 0.0;

	go(120);
	wait1Msec(5000);
	go(-30);
	wait1Msec(1000);
	go(45);
	wait1Msec(1500);
	go(-50);
	wait1Msec(1500);
	go(50);
	wait1Msec(1500);
	go(-50);
	wait1Msec(1500);

	//startGyroTasks();
	//turn(90);

}

task usercontrol() {
	startTask(liftPID);
	startTask(gyroDrift);
	startTask(kFilter);
	while (true) {
		arcadeDrive();
		liftControl();
		lcd();
	}
}
