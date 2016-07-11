/*
 * Motor.h
 *
 *  Created on: Jul 10, 2016
 *      Author: amarnath
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "Utilities.h"

class Motor {

private:

	MotorRotationType motorRotationType;


public:
	Motor();

	virtual ~Motor();

	void setRotationType(MotorRotationType mrt);

	MotorRotationType getRotationType();


};

#endif /* MOTOR_H_ */
