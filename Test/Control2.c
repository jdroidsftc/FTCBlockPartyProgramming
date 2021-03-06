#pragma config(Hubs,  S1, HTServo,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     colorSensor,    sensorI2CHiTechnicColor)
#pragma config(Motor,  mtr_S1_C2_1,     motorRight,    tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     motorLeft,     tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     motorArm,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorFlag,     tmotorTetrix, PIDControl, encoder)
#pragma config(Servo,  srvo_S1_C1_1,    servoClaw,            tServoStandard)
#pragma config(Servo,  srvo_S1_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Tele-Operation Mode Code Template
//
// This file contains a template for simplified creation of an tele-op program for an FTC
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    initializeRobot
//
// Prior to the start of tele-op mode, you may want to perform some initialization on your robot
// and the variables within your program.
//
// In most cases, you may not have to add any code to this function and it will remain "empty".
//
/////////////////////////////////////////////////////////////////////////////////////////////////////


void initializeRobot()
{
	// Place code here to sinitialize servos to starting positions.
	servo[servoClaw] = 0;
	return;
}

int ScaleForMotor(int joyValue)
{
	const int MIN_DEAD_ZONE = -15;
	const int MAX_DEAD_ZONE = 15;
	const int MAX_MOTOR_VAL = 35;
	const float MAX_JOY_VAL = 127.0;

	if ( joyValue < MAX_DEAD_ZONE && joyValue > MIN_DEAD_ZONE)
		return 0;

	int direction = joyValue/abs(joyValue);
	float ratio = joyValue * joyValue /MAX_JOY_VAL * MAX_JOY_VAL;
	int Scaled = ratio * MAX_MOTOR_VAL * direction;
	return Scaled;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Main Task
//
// The following is the main code for the tele-op robot operation. Customize as appropriate for
// your specific robot.
//
// Game controller / joystick information is sent periodically (about every 50 milliseconds) from
// the FMS (Field Management System) to the robot. Most tele-op programs will follow the following
// logic:
//   1. Loop forever repeating the following actions:
//   2. Get the latest game controller / joystick settings that have been received from the PC.
//   3. Perform appropriate actions based on the joystick + buttons settings. This is usually a
//      simple action:
//      *  Joystick values are usually directly translated into power levels for a motor or
//         position of a servo.
//      *  Buttons are usually used to start/stop a motor or cause a servo to move to a specific
//         position.
//   4. Repeat the loop.
//
// Your program needs to continuously loop because you need to continuously respond to changes in
// the game controller settings.
//
// At the end of the tele-op period, the FMS will autonmatically abort (stop) execution of the program.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

task main()
{

	bFloatDuringInactiveMotorPWM = true;
	initializeRobot();


	waitForStart();   // wait for start of tele-op phase

	while (true)
	{
		///////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////
		////                                                   ////
		////      JDROIDS TELE-OP CODE                         ////
		////                                                   ////
		///////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////

		getJoystickSettings(joystick);


		//drive forward, backwards and turn
		if (joy1Btn(2) == 1 ) {  //Drive Forward
			motor[motorLeft] = 35;
			motor[motorRight] = 35;
			wait1Msec(10);
		}
		else {
			if(joy1Btn(3) == 1) {  //Drive Backwards
				motor[motorLeft] = -35;
				motor[motorRight] = -35;
			}
			else { //we need to turn
				motor[motorLeft] = ScaleForMotor(joystick.joy1_y1);
				motor[motorRight] = ScaleForMotor(joystick.joy1_y2);
			}
	  }

	  ////sweeper actions
	  //if(joy1Btn(8) == 1){
	  //	bFloatDuringInactiveMotorPWM = false;
	  //	servo[servoSweeper] = 5;
	  //}
	  //else {
	  //	if(joy1Btn(7) == 1){
	  //		bFloatDuringInactiveMotorPWM = false;
	  //		servo[servoSweeper] = -5;
	  //	}
	  //}

	  bFloatDuringInactiveMotorPWM = true;

	  //Flag Motor
	  if ( joy2Btn(2) == 1 )//A Button
		{
			motor[motorFlag] = 70;
		}
		if( joy2Btn(4) == 1 )//Y Button
		{
			motor[motorFlag] = 0;
		}
		if( joy2Btn(1) == 1 )
		{
			motor[motorFlag] = -50;
		}
	}

}
