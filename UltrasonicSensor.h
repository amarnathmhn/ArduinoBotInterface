/*
 * UltrasonicSensor.h
 *
 *  Created on: Jul 10, 2016
 *      Author: amarnath
 */

#ifndef ULTRASONICSENSOR_H_
#define ULTRASONICSENSOR_H_

#include "Utilities.h"
#include "Environment.h"


class UltrasonicSensor {

private:
	int index;
	float range;
	float val;
	float dSens;

public:

	UltrasonicSensor(); // for simulated robot

	UltrasonicSensor(int idx);  // for real robot

	virtual ~UltrasonicSensor();

	void setRange(float rg);

	void setIndex(int idx);

	void setDSens(float dsens);


	float getRange();

	int getIndex();

	void calcDistance();   // For the actual Sensor

	void calcDistance(Environment* pEnv, Point position, float angle); // For the Simulated Sensor

	float getDistance();

};

#endif /* ULTRASONICSENSOR_H_ */
