/*
 * Motor.cpp
 *
 *  Created on: Jul 10, 2016
 *      Author: amarnath
 */

#include "Motor.h"

Motor::Motor() {
	// TODO Auto-generated constructor stub
	this->motorRotationType = FORWARD;
}

Motor::~Motor() {
	// TODO Auto-generated destructor stub
}

void Motor :: setRotationType(MotorRotationType mrt){

	this->motorRotationType = mrt;

}

MotorRotationType Motor :: getRotationType(){

	return this->motorRotationType;
}

