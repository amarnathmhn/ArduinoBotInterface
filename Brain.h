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
	int* gAction; // group Id
	int* gActionDA; // dopaminergic neurons
	// Connection Id between place and action cells
	int* cId_place_action;
	int* cId_DA_action;
	// Connection Monitor between place and action cells
	ConnectionMonitor* cm_place_action_north;
	ConnectionMonitor* cm_place_action_south;
	ConnectionMonitor* cm_place_action_west;
	ConnectionMonitor* cm_place_action_east;
	// Spike Monitor for Action cells
	SpikeMonitor* sm_action_north;
	SpikeMonitor* sm_action_south;
	SpikeMonitor* sm_action_west;
	SpikeMonitor* sm_action_east;
	// Spike Monitor for Input Cells
	SpikeMonitor* sm_place;
	// Input for Place cells
	PoissonRate* poissRate_place;
	// Agent location
	Point position;
	// Neuron Mapping to actual location
	int reward;
	bool rwEn; // enable reward
	int neuronToReward;
	InteractiveSpikeGenerator* iSpikeGenDANORTH;
	InteractiveSpikeGenerator* iSpikeGenDAWEST;
	InteractiveSpikeGenerator* iSpikeGenDAEAST;
	InteractiveSpikeGenerator* iSpikeGenDASOUTH;
public:
	std::vector<Point> neuronMap;
	std::vector<float> inputFiringRates;
public:
	Brain();
	void createHippocampal(int nPlace, int nAction);
	void setInput(Point position);
	void run(float sec, float msec);
	void setReward(bool en, float reward);
	void setReward(bool en, float reward, int neurToRw);
	void printActionRates();

	virtual ~Brain();

	void setRandomWeights(ConnectionMonitor* cm, float minWt, float maxWt);
	int getNumPlaceCells();
	int getAction();
	void setLocalReward(bool en, float rw, int ActionToRw);
	void setDAReward(float quota, int ActionToRw);
};

#endif /* BRAIN_H_ */
