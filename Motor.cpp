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

void Motor::setRunTime(float rt){
	this->runTime = rt;
}

void Motor:: setRPM(float rpm){
	this->RPM = rpm;
}

float Motor:: getRunTime(){
	return this->runTime;
}

float Motor:: getRPM(){
	return this->RPM;
}

void Motor:: rotateWheel(Wheel* wheel){
	if(this->motorRotationType == FORWARD){
		wheel -> rotate(RPM, runTime);
	}
	else if(this->motorRotationType == BACKWARD){
		wheel -> rotate(-RPM, runTime);
	}else{
		wheel -> rotate(0.0, runTime);
	}
}

