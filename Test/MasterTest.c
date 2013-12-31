#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     colorSensor,    sensorI2CHiTechnicColor)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motorHang,     tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorArm,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     motorLeft,     tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     motorRight,    tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Servo,  srvo_S1_C2_1,    servoScoop,           tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_3,    servoFlag,            tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"


void ArmDown()
{
		motor[motorArm] = -40;
		wait10Msec(10);
}

void ArmUp()
{
		motor[motorArm] = 80;
		wait10Msec(10);
}

void RackUp()
{
	motor[motorHang] = 50;
	wait10Msec(10);
}

void RackDown()
{
	motor[motorHang] = -50;
	wait10Msec(10);
}

void ServoStart()
{
	servo[servoScoop]  = 0;
}

void ServoFlat()
{
	servo[servoScoop] = 100;
}


task main()
{
	while(true)
	{
		servo[servoScoop]  = 0;

		getJoystickSettings(joystick);

		if(joy1Btn(4) == 1)
			ArmUp();
		else if(joy1Btn(2) == 1)
			ArmDown();
		else if (joystick.joy1_TopHat == 0)
			RackUp();
		else if (joystick.joy1_TopHat == 4)
			RackDown();
		else
		{
			motor[motorHang] = 0;
			motor[motorArm] = 0;
		}

		//attempted to use continous rotation servo for flag
		//if( joy1Btn(2) == 1 )
		//	servo[servoFlag] = 256;
		//else if( joy1Btn(1) == 1)
		//	servo[servoFlag] = 127;




		//uncomment the piece that you want tested.
		//servo[servoScoop]  = 100;
		//ArmUp();
		//servo[servoScoop]  = 0;
		//ArmDown();
		//RackUp();
		//RackDown();
		//ServoStart();
		//ServoFlat();
		//servo[servoScoop] = 180;


		//this is a test to see if the github works
		//yes this works
	}
}
