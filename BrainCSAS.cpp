/*
 * BrainCSAS.cpp
 *
 *  Created on: Jul 12, 2016
 *      Author: amarnath
 */

#include "BrainCSAS.h"

BrainCSAS::BrainCSAS(int nAction, int nPlace) {
	// TODO Auto-generated constructor stub
	this->nAction = nAction;
	this->nPlace = nPlace;
	this->neuronToReward = 0;
	this->placeCellFiringRates = NULL;
	this->q = NULL;
	this->rho = new int[nAction];
	this->rwEn = false;
	this->u = new int[nAction]; // mV action potential
	this->urest = -70; // mV resting potential
	this->reward = 0;
	this->neuronMap.resize(nPlace);
	this->inputSpikeSizes = NULL; // create during run
	this->curSimTime = 0;

}

BrainCSAS::~BrainCSAS() {
	// TODO Auto-generated destructor stub
	if (rho)
		delete rho;
	if (u)
		delete u;
}

void BrainCSAS:: setInput(Point position){
	this->position.copy(position);

}
void BrainCSAS:: run(int sec, int msec){
	// pre-generate place cell spike times
	// create place cell firing rates array
	// depending on requirement
	int simTimeMsSlice = sec*1000 + msec;
	this->placeCellFiringRates = new int [nPlace*MAX_SPIKE_BUFFER_SIZE];






}
void BrainCSAS:: printActionRates(){

}
void BrainCSAS:: setRandomWeights(){

}

int BrainCSAS::getAction(){
 return -1;
}
void BrainCSAS::generatePlaceCellSpikeTimes(float rate, int simTimeMsSlice){

	if(!this->placeCellFiringRates){
		printf("BrainCSAS::generatePlaceCellSpikeTimes::placeCellFiringRates not created\n");
		return ;
	}

	// for each place cell
	// generate firing times for the current simulation time
	for()



}

