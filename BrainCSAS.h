/*
 * BrainCSAS.h
 *
 *  Created on: Jul 12, 2016
 *      Author: amarnath
 */

#ifndef BRAINCSAS_H_
#define BRAINCSAS_H_

#include "Utilities.h"
#define MAX_SPIKE_BUFFER_SIZE 1000

class BrainCSAS {
private:
	// Action Cells
	int nAction; // Number
	int nPlace; // group Id
	// Agent location
	Point position;
	// Neuron Mapping to actual location
	int reward;
	bool rwEn; // enable reward
	int neuronToReward;
	float* u;    // to store all membrane potentials
	float* rho;  // probability of firing
	float urest; // resting potentials of all neurons
	float* q;    // synaptic transition probability
	// 1 Dimensional representation. will be of size
	// nPlace*(CurrentSimulationTime in ms)
	// create dynamically as and when required
	int* placeCellFiringRates; // firing rates of place cells
	std::vector<Point> neuronMap; // map of place cells to real location
	int* inputSpikeSizes;
	int curSimTime;
public:
	BrainCSAS(int nAction, int nPlace);
	virtual ~BrainCSAS();
	void setInput(Point position);
	void run(int sec, int msec);
	void printActionRates();
	void setRandomWeights();
	int getNumPlaceCells();
	int getAction();
	void generatePlaceCellSpikeTimes(float rate);
};

#endif /* BRAINCSAS_H_ */
