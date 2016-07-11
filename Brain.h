/*
 * Brain.h
 *
 *  Created on: Jul 11, 2016
 *      Author: amarnath
 */

#ifndef BRAIN_H_
#define BRAIN_H_

#include "carlsim.h"
#include "math.h"
class Brain {

private:
	// Simulation Object
	CARLsim* sim;
	// Place Cells
	int nPlace;  // Number
	int gPlace;  // group Id
	// Action Cells
	int nAction; // Number
	int gAction; // group Id
	// Connection Id between place and action cells
	int cId_place_action;
	// Connection Monitor between place and action cells
	ConnectionMonitor* cm_place_action;
	// Spike Monitor for Action cells
	SpikeMonitor* sm_action;
	// Input for Place cells
	PoissonRate* poissRate_place;
public:
	Brain();
	void createHippocampal(int nPlace, int nAction);
	virtual ~Brain();

	void setRandomWeights(ConnectionMonitor* cm, float minWt, float maxWt);
};

#endif /* BRAIN_H_ */
