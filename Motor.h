/*
 * Motor.h
 *
 *  Created on: Jul 10, 2016
 *      Author: amarnath
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "Utilities.h"
#include "Wheel.h"

class Motor {

private:

	MotorRotationType motorRotationType;
	float runTime;
	float RPM;


public:
	Motor();

	virtual ~Motor();

	void setRotationType(MotorRotationType mrt);

	MotorRotationType getRotationType();

	void setRunTime(float rt);

	void setRPM(float rpm);

	float getRunTime();

	float getRPM();

	void rotateWheel(Wheel* wheel);


};

#endif /* MOTOR_H_ */
