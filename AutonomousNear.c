#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S3,     IRSensor,       sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     motorLeft,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorRight,    tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     motorArm,      tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     motorFlag,     tmotorTetrix, PIDControl, encoder)
#pragma config(Servo,  srvo_S1_C3_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
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
const int FORWARD = 1;
const int BACKWARD = 2;

/////////////////////////////////////////////////////////////////////////////////////////////////////
//constants needed to caluclate distance
/////////////////////////////////////////////////////////////////////////////////////////////////////
const int ONE_REVOLUTION  = 1440; 	// one revolution = 1440 Ticks
const int WHEEL_DIAMETER = 4;  			// current wheel diameter = 4 inches
const float PI = 3.14159265359;

//should find the fourth basket within 45 inches from the start position
const int BASKET_ZONE4_MAX  = (ONE_REVOLUTION/(PI * WHEEL_DIAMETER)) * -45 ;


#include "JoystickDriver.c"  							//Include file to "handle" the Bluetooth messages.
#include "Drivers/Common.h"
#include "Drivers/hitechnic-colour-v2.h"
#include "Drivers/hitechnic-irseeker-v2.h"
#include "JDroidsHelperFunctions.c"				//Include file to "handle" JDroids functions.




//////////////////////////////////////////////////////////////////////////////////////
//
// TurnRight Backwards
//
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
//
// SwingTurnLeft
// Used in two places
// 	1. when turned towards the basket
//  2. when turned towards the ramp
//////////////////////////////////////////////////////////////////////////////////////
void SwingTurnLeft()
{
		nMotorEncoder[motorRight] = 0;
		nMotorEncoder[motorLeft] = 0;

		nMotorEncoderTarget[motorRight] = 1400;
		nMotorEncoderTarget[motorLeft] = 1400;

		motor[motorRight] = 30;
		motor[motorLeft] = -30;

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

		nMotorEncoderTarget[motorRight] = 1400;
		nMotorEncoderTarget[motorLeft] = 1400;

		motor[motorRight] = -30;
		motor[motorLeft] = 30;

		while(nMotorRunState[motorRight] != runStateIdle || nMotorRunState[motorLeft] != runStateIdle)
		{
		}

		motor[motorRight] = 0;
		motor[motorLeft] = 0;
}

//////////////////////////////////////////////////////////////////////////////////////
//
// SwingTurnLeftRamp
//
//////////////////////////////////////////////////////////////////////////////////////
void SwingTurnLeftRamp()
{
		nMotorEncoder[motorRight] = 0;
		nMotorEncoder[motorLeft] = 0;

		nMotorEncoderTarget[motorRight] = 1400;
		nMotorEncoderTarget[motorLeft] = 1400;

		motor[motorRight] = 30;
		motor[motorLeft] = -30;

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

  // Place code here to initialize servos to starting positions.
  // Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.

	//IR Mode set
  tHTIRS2DSPMode _mode = DSP_1200;
	HTIRS2setDSPMode(IRSensor, _mode);

	//block drop servo motor position
	//servo[servoClaw] = 10;
	wait1Msec(1000);
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
	motor[motorRight] = 35;
	motor[motorLeft] = 35;

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
		if (currentTicks <= BASKET_ZONE4_MAX )
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
void DropBlock()
{
	  Move(4,FORWARD, 20);
    wait1Msec(10);
  //Swing Turn into the Basket, to position the robot for dropping the block
    SwingTurnLeft();
	  wait1Msec(10);
	//Move closer to the robot
	  Move(6,BACKWARD, 35);
	  wait1Msec(10);
	//Drop the block, hopefully, into the basket
	  //servo[servoClaw] = 110;
	  wait1Msec(1000);
	  //servo[servoClaw] = 5;
	  Move(2,FORWARD,35);
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
  initializeRobot();

  //waitForStart(); // Wait for the beginning of autonomous phase.

	///////////////////////////////////////////////////////
  //
  //start of JDroids Autonomous Code
  //
  ///////////////////////////////////////////////////////

  //Coast the motors
 	bFloatDuringInactiveMotorPWM = true;

 	///////////////////////////////////////////////////////
 	//
 	// Detect the IR beam, we get out when 5 is detected
 	// returns the number of ticks moved
 	//
 	///////////////////////////////////////////////////////
 	int currentTicks = MoveUntilIR();
  wait10Msec(30);

  ///////////////////////////////////////////////////////
  //
  //Yay! We detected the beam!
  //Its about time we drop the block in the basket
  //
  ///////////////////////////////////////////////////////
  DropBlock();

  ////////////////////////////////////////////////////////
  //
  //okay, Now what?! Backup from basket
  //
  ///////////////////////////////////////////////////////
  Move(1, FORWARD, 40);
  wait10Msec(30);
  SwingTurnRight();


  ///////////////////////////////////////////////////////
  //
  // Logic below determines how much backward robot needs
  // based on which basket the block was dropped
  //
  ///////////////////////////////////////////////////////

  nMotorEncoder[motorLeft] = 0;
  nMotorEncoder[motorRight]= 0;
  nMotorEncoderTarget[motorLeft] =  (currentTicks * -1)-1150;
  nMotorEncoderTarget[motorRight] =  (currentTicks * -1)-1150;

  motor[motorLeft] = -40;
  motor[motorRight] = -40;
  while ( nMotorRunState[motorLeft] != runStateIdle || nMotorRunState[motorRight] != runStateIdle)
  {
  }
  motor[motorLeft] = 0;
  motor[motorRight] = 0;
  wait10Msec(20);

  ///////////////////////////////////////////////////////
  //
	// Final Step, We are almost there, Climb the ramp
  //
  ///////////////////////////////////////////////////////

	//turnleft towards the ramp
	SwingTurnLeftRamp();
	wait10Msec(20);

	//Find the Blue or RED line
	MoveUntilBlueOrRed();
	wait10Msec(20);

	//postion towards the ramp
	TurnRight();
	wait10Msec(30);

	//brakes so that robot does not slide down ramp
	bFloatDuringInactiveMotorPWM = false;

	//climb the ramp
	Move(27,FORWARD,60);

	///////////////////////////////////////////////////////
  //
	// We are done
  //
  ///////////////////////////////////////////////////////

  while (true)
	{

	}

}
