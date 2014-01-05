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
task main()
{
	while(true)
	{
	motor[motorRight] = 30;
	motor[motorLeft] = 30;
}

}
