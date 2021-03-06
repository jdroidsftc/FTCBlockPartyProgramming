#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  HTMotor)
#pragma config(Sensor, S2,     IRSensor,       sensorI2CCustom)
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


task main()
{



}
