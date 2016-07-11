/*
 * Wheel.cpp
 *
 *  Created on: Jul 10, 2016
 *      Author: amarnath
 */

#include "Wheel.h"

Wheel::Wheel() {
	// TODO Auto-generated constructor stub
	this->diameter = 10.0 ; // wheel diameter
	this->nSlots = 24; // encoder slots
	this->dAngle = 0.0; // radians
	this->totalAngle = 0.0; // radians

}

Wheel::~Wheel() {
	// TODO Auto-generated destructor stub
}

void Wheel::rotate(float RPM, float runTime){
	// No. of Rotations * PI
	dAngle = 3.14*RPM*runTime/60.0;
	totalAngle += dAngle;
}

int Wheel::getSlotsPassed(){
	// nSlots for complete rotation
	// Calculate for RPM*time no of rotations
	return int(nSlots*dAngle/(2*3.14));
}

float Wheel:: getAngleRotated(){
	return this->dAngle;
}

float Wheel:: getDiameter(){
	return this->diameter;
}
