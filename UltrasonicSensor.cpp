/*
 * UltrasonicSensor.cpp
 *
 *  Created on: Jul 10, 2016
 *      Author: amarnath
 */

#include "UltrasonicSensor.h"

UltrasonicSensor::UltrasonicSensor() {
	// TODO Auto-generated constructor stub
	this-> range = 200; // pixels in simulation
	this-> index = 0;
	this-> val = 0;
}

UltrasonicSensor::UltrasonicSensor(int idx) {
	// TODO Auto-generated constructor stub
	this-> range = 200; // pixels in simulation
	this-> index = idx;
	this-> val = 0;
}

UltrasonicSensor::~UltrasonicSensor() {
	// TODO Auto-generated destructor stub
}

void UltrasonicSensor::setRange(float rg){
	this->range = rg;
}

void UltrasonicSensor::setIndex(int idx){
	this->index = idx;
}

void UltrasonicSensor::setDSens(float dSens){
	this->dSens = dSens;
}
float UltrasonicSensor::getRange(){
	return this->range;
}

int UltrasonicSensor::getIndex(){
	return this->index;
}

void UltrasonicSensor::calcDistance(){
	// write NewPing Code for Arduino
}

void UltrasonicSensor::calcDistance(Environment* pEnv){
	// write range sensing code for allegro environment

}

float UltrasonicSensor ::getDistance(){
	return this->val;
}

