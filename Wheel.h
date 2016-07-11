/*
 * Wheel.h
 *
 *  Created on: Jul 10, 2016
 *      Author: amarnath
 */

#ifndef WHEEL_H_
#define WHEEL_H_

class Wheel {

private:
	float diameter;
	float nSlots;
	float dAngle;
	float totalAngle;

public:
	Wheel();
	virtual ~Wheel();
	void rotate(float RPM, float runTime);
	int getSlotsPassed();
};

#endif /* WHEEL_H_ */
