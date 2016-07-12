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
#include <cstdlib>
#include "Utilities.h"

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
	// Agent location
	Point position;
	// Neuron Mapping to actual location
public:
	std::vector<Point> neuronMap;
	std::vector<float> inputFiringRates;
public:
	Brain();
	void createHippocampal(int nPlace, int nAction);
	void setInput(Point position);
	void run(float sec, float msec);


	virtual ~Brain();

	void setRandomWeights(ConnectionMonitor* cm, float minWt, float maxWt);
	int getNumPlaceCells();
};

#endif /* BRAIN_H_ */
