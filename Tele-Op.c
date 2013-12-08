#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     colorSensor,    sensorI2CHiTechnicColor)
#pragma config(Motor,  mtr_S1_C1_1,     motorHang,     tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorArm,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     motorLeft,     tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     motorRight,    tmotorTetrix, PIDControl, reversed, encoder)
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

const int MAX_ENCODER_HANG = 27800;

void initializeRobot()
{
	// Place code here to sinitialize servos to starting positions.
	servo[servoScoop] = 0;
  return;
}

task raiseRack()
{
		getJoystickSettings(joystick);
		nMotorEncoder[motorHang] = 0;
		nMotorEncoderTarget[motorHang] = MAX_ENCODER_HANG;
		motor[motorHang] = 50;
		while( (nMotorRunState[motorHang] != runStateIdle) && (joy2Btn(6) != 1)  && (joy2Btn(5) != 1) ) //Right/left bumper is an emergency stop
		{
		}
		motor[motorHang] = 0;
}

int ScaleForMotor(int joyValue)
{
	const int MIN_DEAD_ZONE = -7;
	const int MAX_DEAD_ZONE = 7;
	const int MAX_MOTOR_VAL = 85;
	const float MAX_JOY_VAL = 127;

	if ( joyValue < MAX_DEAD_ZONE && joyValue > MIN_DEAD_ZONE)
		return 0;

	int direction = joyValue/abs(joyValue);
	float ratio = ((joyValue * joyValue) / (MAX_JOY_VAL * MAX_JOY_VAL));
	int Scaled = ratio * MAX_MOTOR_VAL * direction;
	return Scaled;
}


int ScaleForServo(int joyValue)
{

	const int MIN_DEAD_ZONE = -7;
	const int MAX_DEAD_ZONE = 7;
	const int MAX_SERVOVAL  = 255;
	const float MAX_JOY_VAL = 127;

	if ( joyValue < MAX_DEAD_ZONE && joyValue > MIN_DEAD_ZONE)
		return 0;

	int direction = joyValue/abs(joyValue);
	float ratio = ((joyValue * joyValue) / (MAX_JOY_VAL * MAX_JOY_VAL));
	int Scaled = ratio * MAX_SERVOVAL * direction;
	return Scaled;
}


task Arm()
{
	while(true)
	{
		getJoystickSettings(joystick);
		motor[motorArm] = ScaleForMotor(joystick.joy2_y2);
	}
}

task Scoop()
{
	const int MIN_DEAD_ZONE = -7;
	const int MAX_DEAD_ZONE = 7;
	const int MAX_SERVOVAL  = 255;
	const float MAX_JOY_VAL = 127;
	int LastValue = 0;
	while ( 1)
	{

		getJoystickSettings(joystick);
		int joyValue = joystick.joy2_y1;
		if ( joyValue < MAX_DEAD_ZONE && joyValue > MIN_DEAD_ZONE)
				servo[servoScoop] = ServoValue[servoScoop];
		else
		{
			int direction = joyValue/abs(joyValue);
			float ratio = ((joyValue * joyValue) / (MAX_JOY_VAL * MAX_JOY_VAL));
			int Scaled = ratio * MAX_SERVOVAL * direction;

			if(LastValue < Scaled )
			{
				servo[servoScoop] = ServoValue[servoScoop]  - 2;
			}
			else
			{
				servo[servoScoop] = ServoValue[servoScoop]  + 2;
			}
		}
	}
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

	initializeRobot();
	motor[motorRight] = 0;
	motor[motorLeft] = 0;
	motor[motorFlag] =0;
	motor[motorHang] =0;
	motor[motorArm] = 0;

	StartTask(Arm);
	StartTask(Scoop);

	while (true)
	{
		///////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////
		////                                                   ////
		////      JDROIDS TELE-OP CODE                         ////
		////                                                   ////
		///////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////

		bFloatDuringInactiveMotorPWM = true;

		getJoystickSettings(joystick);


		//drive controls
		if ( joystick.joy1_TopHat == 0 ) //forward
		{
				motor[motorRight] = 70;
				motor[motorLeft] = 70;
		}
		else if ( joystick.joy1_TopHat  == 4 )//backward
		{
				motor[motorRight] = -50;
				motor[motorLeft] = -50;
		}
		else if ( joystick.joy1_TopHat  == 2 )//point turn left
		{
				motor[motorLeft] = 60;
				motor[motorRight] = -60;
		}
		else if ( joystick.joy1_TopHat == 1 ) //swing right
		{
				motor[motorRight] = 20;
				motor[motorLeft] = 60;
		}
		else if ( joystick.joy1_TopHat  == 6 ) //point turn right
		{
				motor[motorRight] = 60;
				motor[motorLeft] = -60;
		}
		else if ( joystick.joy1_TopHat == 7 ) //swing left
		{
				motor[motorRight] = 60;
				motor[motorLeft] = 20;
		}
		else if (joy1Btn(2) == 1)  //move backward slowly
		{
					motor[motorRight] = -20;
					motor[motorLeft] = -20;
		}
		else if (joy1Btn(7) == 1) //ramp up
		{
					bFloatDuringInactiveMotorPWM = false;
					motor[motorRight] = 30;
					motor[motorLeft] = 30;
		}
		else if (joy1Btn(8) == 1) //ramp down
		{
					bFloatDuringInactiveMotorPWM = false;
					motor[motorRight] = -30;
					motor[motorLeft] = -30;
		}
		else
		{
			motor[motorLeft] = ScaleForMotor( joystick.joy1_y1 );
			motor[motorRight] = ScaleForMotor( joystick.joy1_y2 );
		}



/*		//worm gear arm control
		if(joy2Btn(3) == 1) //B = up
		{
			motor[motorArm] = 40;
		}
		else if( joy2Btn(2) == 1) //A = down
		{
			motor[motorArm] = -40;
		}
		else
		{
			motor[motorArm] = 0;
		}
*/
		//flag control
		if  (joy2Btn(8) == 1) //right trigger spin
		{
			motor[motorFlag] = 50;
		}
		else if  (joy2Btn(7) == 1) //left trigger stop
		{
			motor[motorFlag] = 0;
		}
/*
		//servo scoop control
		if(joy2Btn(1) == 1) //X - scoop up
		{
					servo[servoScoop] = ServoValue[servoScoop] + 2;
		}
		else if(joy2Btn(4) == 1) //Y - scoop down
		{
					servo[servoScoop] = ServoValue[servoScoop]  - 2;
		}
		*/

		//rack and pinion - hanging mechanism
		else if (joystick.joy2_TopHat == 0 ) //up
		{
				StartTask(raiseRack);
	  }
	  else if (joystick.joy2_TopHat == 4 ) //down
	  {
	  		nMotorEncoder[motorHang] = 0;
				nMotorEncoderTarget[motorHang] = -(MAX_ENCODER_HANG/2);
				motor[motorHang] = -50;
				while((nMotorRunState[motorHang] != runStateIdle) && (joy2Btn(6) != 1)  && (joy2Btn(5) != 1) ) //Right/left bumper is an emergency stop
				{
				}
				motor[motorHang] = 0;
	  }

		//flag control


	} //while true

} // main
