#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     IRSensor,       sensorI2CCustom)
#pragma config(Sensor, S4,     sonarSensor,    sensorSONAR)
#pragma config(Motor,  mtr_S1_C1_1,     motorHang,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorArm,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     motorLeft,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorRight,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     motorFlag,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     motorI,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    servoScoop,           tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Autonomous Mode Code Template
//
// This file contains a template for simplified creation of an autonomous program for an TETRIX robot
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////
//constants for direction of the drive
/////////////////////////////////////////////////////////////////////////////////////////////////////
const int FORWARD = 2;
const int BACKWARD = 1;

/////////////////////////////////////////////////////////////////////////////////////////////////////
//constants needed to caluclate distance
/////////////////////////////////////////////////////////////////////////////////////////////////////
const int ONE_REVOLUTION  = 1440; 	// one revolution = 1440 Ticks
const int WHEEL_DIAMETER = 4;  			// current wheel diameter = 4 inches
const float PI = 3.14159265359;

//should find the fourth basket within 45 inches from the start position
const int BASKET_ZONE4_MAX  = (ONE_REVOLUTION/(PI * WHEEL_DIAMETER)) * 50 ;
const int BASKET_ZONE3_MAX = (ONE_REVOLUTION/(PI * WHEEL_DIAMETER)) * 45;

#include "JoystickDriver.c"  							//Include file to "handle" the Bluetooth messages.
#include "Drivers/Common.h"
#include "Drivers/hitechnic-colour-v2.h"
#include "Drivers/hitechnic-irseeker-v2.h"
#include "JDroidsHelperFunctions.c"				//Include file to "handle" JDroids functions.



//////////////////////////////////////////////////////////////////////////////////////
// TurnRight Backwards
//////////////////////////////////////////////////////////////////////////////////////
void TurnRight()
{
		nMotorEncoder[motorRight] = 0;
		nMotorEncoder[motorLeft] = 0;

		nMotorEncoderTarget[motorRight] = 0;
		nMotorEncoderTarget[motorLeft] = 2800;

		motor[motorRight] = 0;
		motor[motorLeft] = 60;

		while(nMotorRunState[motorLeft] != runStateIdle)
		{
		}

		motor[motorRight] = 0;
		motor[motorLeft] = 0;
}


//////////////////////////////////////////////////////////////////////////////////////
// SwingTurnLeft
// when turned towards the basket
//////////////////////////////////////////////////////////////////////////////////////
void SwingTurnLeft()
{
		nMotorEncoder[motorRight] = 0;
		nMotorEncoder[motorLeft] = 0;

		nMotorEncoderTarget[motorRight] = 2000;
		nMotorEncoderTarget[motorLeft] = 2000;

		motor[motorRight] = 50;
		motor[motorLeft] = -50;

		while(nMotorRunState[motorRight] != runStateIdle || nMotorRunState[motorLeft] != runStateIdle)
		{
		}

		motor[motorRight] = 0;
		motor[motorLeft] = 0;
}


//////////////////////////////////////////////////////////////////////////////////////
// SwingTurnRight
//////////////////////////////////////////////////////////////////////////////////////
void SwingTurnRight()
{
		nMotorEncoder[motorRight] = 0;
		nMotorEncoder[motorLeft] = 0;

		nMotorEncoderTarget[motorRight] = 2000;
		nMotorEncoderTarget[motorLeft] = 2000;

		motor[motorRight] = -45;
		motor[motorLeft] = 45;

		while(nMotorRunState[motorRight] != runStateIdle || nMotorRunState[motorLeft] != runStateIdle)
		{
		}

		motor[motorRight] = 0;
		motor[motorLeft] = 0;
}


//////////////////////////////////////////////////////////////////////////////////////
// SwingTurnRight2
//////////////////////////////////////////////////////////////////////////////////////
void SwingTurnRight2(int ThirdOrFourthBasket)
{
		nMotorEncoder[motorRight] = 0;
		nMotorEncoder[motorLeft] = 0;

		if ( ThirdOrFourthBasket == 1 )
		{
			nMotorEncoderTarget[motorRight] = 1200;
			nMotorEncoderTarget[motorLeft] = 1200;
		}
		else
		{
			nMotorEncoderTarget[motorRight] = 2200;
			nMotorEncoderTarget[motorLeft] = 2200;
		}

		motor[motorRight] = -45;
		motor[motorLeft] = 45;

		while(nMotorRunState[motorRight] != runStateIdle || nMotorRunState[motorLeft] != runStateIdle)
		{
		}

		motor[motorRight] = 0;
		motor[motorLeft] = 0;
}

//////////////////////////////////////////////////////////////////////////////////////
// SwingTurnLeftRamp
//////////////////////////////////////////////////////////////////////////////////////
void SwingTurnRightRamp()
{
		nMotorEncoder[motorRight] = 0;
		nMotorEncoder[motorLeft] = 0;

		nMotorEncoderTarget[motorRight] = 1200;
		nMotorEncoderTarget[motorLeft] = 1200;

		motor[motorRight] = -50;
		motor[motorLeft] = 50;

		while(nMotorRunState[motorRight] != runStateIdle || nMotorRunState[motorLeft] != runStateIdle)
		{
		}

		motor[motorRight] = 0;
		motor[motorLeft] = 0;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    initializeRobot
//
//
//   1. Move motors and servos to a preset position.
//   2. Some sensor types take a short while to reach stable values during which time it is best that
//      robot is not moving.
//
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
void initializeRobot()
{
  // Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.

	//IR Mode set
  tHTIRS2DSPMode _mode = DSP_1200;
	HTIRS2setDSPMode(IRSensor, _mode);

	//block drop servo motor position
	servo[servoScoop] = 0;
	return;

}

//////////////////////////////////////////////////////////////////////////////////////
//
// IR Functions
//
//////////////////////////////////////////////////////////////////////////////////////
int  MoveUntilIR()
{
	//1. Reset the encoders
	nMotorEncoder[motorRight] = 0;
	nMotorEncoder[motorLeft] = 0;

	//2. Start the motors
	motor[motorRight] = 45;
	motor[motorLeft] = 52;

	//3. Set the variables to track the numbe of revolutions, so robot knows its position on the field
	int currentTicks = 0;
	string sTemp;

	// 4. Detect the IR beam
	// Read direction from the IR in a while loop
	// While loop exits, if either 5 is detected or if robot is past the 4th basket

	int direction = HTIRS2readACDir(IRSensor);
	while(  direction != 5  )  {
		// read the direction
		direction = HTIRS2readACDir(IRSensor);

		// read the number of ticks - that is how far the robot has moved since it started
		currentTicks = nMotorEncoder[motorRight];

		// check to see if we are past the 4th basket
		if (currentTicks >= BASKET_ZONE4_MAX )
		{
	  	//IR Seeker did not detect the IR beam, we are way past the 4th basket,
	    //need to stop moving
	    break;
		}
		sprintf(sTemp, "%d", currentTicks);
		nxtDisplayString(2, sTemp);
	}

	//5. Stop moving
	motor[motorRight] = 0;
	motor[motorLeft] = 0;
	//6. Return Ticks Moved
	return currentTicks;
}

//////////////////////////////////////////////////////////////////////////////////////
//
// Drop Block
//
//////////////////////////////////////////////////////////////////////////////////////
//Drop Block NEW
void DropBlock()
{
	Move(6, FORWARD, 45);
	wait10Msec(10);

	SwingTurnLeft();

	Move(3, BACKWARD, 45);

	servo[servoScoop] = 50;

	motor[motorArm] = 45;
	wait10Msec(75);

	servo[servoScoop] = 105;

	motor[motorArm] = 45;
	wait10Msec(180);

	servo[servoScoop] = 135;

	motor[motorArm] = 50;
	wait10Msec(25);

	motor[motorArm] = 0;

	Move(9, FORWARD, 35);
	wait1Msec(10);

	servo[servoScoop] = 255;
	wait10Msec(125);

	servo[servoScoop] = 0;
}


task RaiseRack()
{
 		nMotorEncoder[motorHang] = 0;
		nMotorEncoderTarget[motorHang] = 700;
		motor[motorHang] = 50;
		while( nMotorRunState[motorHang] != runStateIdle )
		{
		}
		motor[motorHang] = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Main Task
//
// The following is the main code for the autonomous robot operation.
//
// Sequence of Operations:
//
// 1. Detect the IR beam
// 2. Turn and Drop the block
// 3. Find the Blue or Red Line
// 4. Climb the Ramp
//
// At the end of the autonomous period, the FMS will autonmatically abort execution of the program.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

task main()
{

	//initialize the servos
  initializeRobot();

	// Wait for the beginning of autonomous phase.
  waitForStart();

  // move the arm up so that the robot can move easily
	motor[motorArm] = 65;
  wait1Msec(1000);
  motor[motorArm] = 0;

	// raise the rack so that the robot can move easily
  StartTask(RaiseRack);

	wait10Msec(1); //wait a little for the threads to start

  // Coast the motors
 	bFloatDuringInactiveMotorPWM = true;

 	// Detect the IR beam, we get out when 5 is detected
 	// returns the number of ticks moved
 	int currentTicks = MoveUntilIR();
  wait10Msec(10);

  //Yay! We detected the beam, time to drop the block in the basket
  DropBlock();

  //back away from the basket
 	Move(2, BACKWARD, 35);

	// turn back
  SwingTurnRight();

  // Logic below determines how much backward robot needs
  // based on which basket the block was dropped
  nMotorEncoder[motorLeft] = 0;
  nMotorEncoder[motorRight]= 0;

  //dont go to the start position, start a bit before, so that wall will not be touched
  nMotorEncoderTarget[motorLeft] =  (currentTicks * -1)  + 550;
  nMotorEncoderTarget[motorRight] =  (currentTicks * -1) + 550;

  motor[motorLeft] = -60;
  motor[motorRight] = -60;
  while ( nMotorRunState[motorLeft] != runStateIdle || nMotorRunState[motorRight] != runStateIdle)
  {

  }
  motor[motorLeft] = 0;
  motor[motorRight] = 0;
  wait10Msec(5);

  //turnright towards the ramp
	SwingTurnRightRamp();
	wait10Msec(5);

	//go back a bit for more clearance
	Move(38, BACKWARD, 60);
	wait10Msec(5);

	//postion towards the ramp
	if(currentTicks > BASKET_ZONE3_MAX )
	{
		//turn less
		SwingTurnRight2(1);
	}
	else
	{
		//turn more
		SwingTurnRight2(0);
	}
	wait10Msec(5);

	//brakes so that robot does not slide down ramp
	bFloatDuringInactiveMotorPWM = false;

	//climb the ramp partly
	if(currentTicks < BASKET_ZONE3_MAX)
		Move(23.5,BACKWARD,60);
	else
		Move(20, BACKWARD, 60);

	//check for other robots
	if(SensorValue[sonarSensor] <= 75) //if obstruction is present, max power
		Move(13.5, BACKWARD, 100);
	else if(SensorValue[sonarSensor] > 75)
		Move(10, BACKWARD, 60);

	// We are done
  while (true)
	{

	}

}
