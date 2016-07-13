/*
 * Brain.cpp
 *
 *  Created on: Jul 11, 2016
 *      Author: amarnath
 */

#include "Brain.h"

Brain::Brain() {

	sim = new CARLsim("Brain Controller", CPU_MODE, USER);
	this->gAction = NULL;
	this->gPlace = 0;
	this->cId_place_action = NULL;
	this->nAction = 3;
	this->nPlace = 100;
	this->poissRate_place = NULL;
	this->sm_place = NULL;
	this->rwEn = false;
	this->reward = 1.0;
	this->neuronToReward = 0.0;
	this->gActionDA = NULL;
	this->cId_DA_action = NULL;

	this->cm_place_action_east = NULL;
	this->cm_place_action_west = NULL;
	this->cm_place_action_north = NULL;
	this->cm_place_action_south = NULL;

	this->sm_action_east = NULL;
	this->sm_action_west = NULL;
	this->sm_action_north = NULL;
	this->sm_action_south = NULL;

	this->iSpikeGenDAEAST = NULL;
	this->iSpikeGenDANORTH = NULL;
	this->iSpikeGenDASOUTH = NULL;
	this->iSpikeGenDAWEST = NULL;


}

Brain::~Brain() {
	// TODO Auto-generated destructor stub
	if (sim)
		delete sim;
	if (poissRate_place)
		delete poissRate_place;
	if (gAction)
		delete gAction;
	if (gActionDA)
		delete gActionDA;
	if (cId_place_action)
		delete cId_place_action;

	if(cId_DA_action) delete cId_DA_action;
}

void Brain::setRandomWeights(ConnectionMonitor* connMon, float minWt,
		float maxWt) {
	int nNeurPre = connMon->getNumNeuronsPre();
	int nNeurPost = connMon->getNumNeuronsPost();
	int connId = connMon->getConnectId();

	for (int s = 0; s < nNeurPre; s++) {
		for (int a = 0; a < nNeurPost; a++) {

			float w = minWt
					+ static_cast<float>(rand())
							/ (static_cast<float>(RAND_MAX / (maxWt - minWt)));
			//printf("random weight w = %f\n", w);
			sim->setWeight(connId, s, a, w, false);

		}
	}
	connMon->print();
}

void Brain::createHippocampal(int nPlace, int nAction) {

	// resize the neuronmap to number of place cells
	//this->neuronMap.resize(nPlace);
	this->inputFiringRates.resize(nPlace);

	// Create Brain Here
	// Hardcoded Izhikevich Neurons
	this->nPlace = nPlace;   // 10x10 grid of 100 Neurons
	this->nAction = nAction;    // 3 Action Neurons
	this->gAction = new int[nAction];
	this->gActionDA = new int[nAction];
	this->cId_place_action = new int[nAction];
	this->cId_DA_action = new int[nAction];


	if (!sim) {
		printf("Brain::createHippocampal: failed because sim is NULL\n");
	}
	this->gPlace = sim->createSpikeGeneratorGroup("PlaceCells", nPlace,EXCITATORY_NEURON);

	stdpType_t stdpType = DA_MOD;
	float ex_a = 0.02, ex_b = 0.2, ex_c = -65.0f, ex_d = 8.0f;
	float in_a = 0.1, in_b = 0.25, in_c = -65.0f, in_d = 2.0f;

	// in this loop:
	// create action groups for all actions
	// create connections to place cells and all actions
	for (int ga = 0; ga < nAction; ga++){

		this->gActionDA[ga] = sim->createSpikeGeneratorGroup("ActionDA", 1, DOPAMINERGIC_NEURON );
	}
	iSpikeGenDANORTH = new InteractiveSpikeGenerator(1,1);
    iSpikeGenDAWEST = new InteractiveSpikeGenerator(1,1);
	iSpikeGenDAEAST = new InteractiveSpikeGenerator(1,1);
	iSpikeGenDASOUTH = new InteractiveSpikeGenerator(1,1);
	if(!iSpikeGenDANORTH || !iSpikeGenDAWEST || !iSpikeGenDAEAST || !iSpikeGenDASOUTH){
		printf("Brain::createHippocampal: one of iSpikeGens is null\n");
		return ;
	}
	for (int ga = 0; ga < nAction; ga++){
		//this->iSpikeGeniDA.push_back(new InteractiveSpikeGenerator(1,/*ISI*/ 1));
		this->gAction[ga] = sim->createGroup("Action", 1,EXCITATORY_NEURON);
	}

	for (int ga = 0; ga < nAction; ga++){
		this->cId_place_action[ga] = sim->connect(gPlace, gAction[ga], "full",
				RangeWeight(0, 0.1, 2.0), 1.0f, RangeDelay(1.0f), RadiusRF(-1),
				SYN_PLASTIC);
	}
	for (int ga = 0; ga < nAction; ga++){
		this->cId_DA_action[ga] = sim->connect(gActionDA[ga], gAction[ga], "full",
				10.0, 1.0f, RangeDelay(1.0f), RadiusRF(-1),
				SYN_FIXED);
	}

	for (int ga = 0; ga < nAction; ga++){

		this->sim->setESTDP(gAction[ga], true, stdpType,
				ExpCurve(0.0001, 20.0, -0.0015, 20.0));
	}
	for (int ga = 0; ga < nAction; ga++){
		this->sim->setNeuronParameters(gAction[ga], ex_a, ex_b, ex_c, ex_d);
	}
	for (int ga = 0; ga < nAction; ga++){
		//this->sim->setSpikeGenerator(gActionDA[ga], iSpikeGenDA[ga]);
	}
	sim->setSpikeGenerator(gActionDA[NORTH], iSpikeGenDANORTH);
	sim->setSpikeGenerator(gActionDA[WEST], iSpikeGenDAWEST);
	sim->setSpikeGenerator(gActionDA[EAST], iSpikeGenDAEAST);
	sim->setSpikeGenerator(gActionDA[SOUTH], iSpikeGenDASOUTH);



	sim->setWeightAndWeightChangeUpdate(INTERVAL_10MS, true, 0.90f);
	sim->setConductances(true);

	sim->setupNetwork();

	//******************************* CREATE MONITORS **********************************************//
	//for (int ga = 0; ga < nAction; ga++) {
	cm_place_action_north = sim->setConnectionMonitor(gPlace, gAction[NORTH], "DEFAULT");
	cm_place_action_west = sim->setConnectionMonitor(gPlace, gAction[WEST], "DEFAULT");
	cm_place_action_east = sim->setConnectionMonitor(gPlace, gAction[EAST], "DEFAULT");
	cm_place_action_south = sim->setConnectionMonitor(gPlace, gAction[SOUTH], "DEFAULT");
	//}
	sm_action_north = sim->setSpikeMonitor(gAction[NORTH], "DEFAULT");
	sm_action_south = sim->setSpikeMonitor(gAction[SOUTH], "DEFAULT");
	sm_action_east = sim->setSpikeMonitor(gAction[EAST], "DEFAULT");
	sm_action_west = sim->setSpikeMonitor(gAction[WEST], "DEFAULT");

	this->sm_place = sim->setSpikeMonitor(gPlace, "DEFAULT");

	srand(static_cast<unsigned>(time(0)));
	//for (int ga = 0; ga < nAction; ga++) {
    setRandomWeights(cm_place_action_north, 0, 2.);
    setRandomWeights(cm_place_action_south, 0, 2.);
    setRandomWeights(cm_place_action_west, 0, 2.);
    setRandomWeights(cm_place_action_east, 0, 2.);
	//}

	//printf("DEBUG:: hippocampal exiting...\n");
	this->poissRate_place = new PoissonRate(nPlace);
	this->poissRate_place->setRates(10.0);

	sim->setSpikeRate(gPlace, poissRate_place);
}

void Brain::setInput(Point pos) {
	this->position.copy(pos);

	// Calculate Firing Rates as mentioned in the paper
	this->inputFiringRates.resize(nPlace);
	float sigma = 200;
	for (int n = 0; n < nPlace; n++) {

		//neuronMap[n].print();
		//position.print();

		float fmax = 10.;
		float f = fmax
				* exp(
				       -position.getSquareDist(neuronMap[n])
								/ (2 * sigma * sigma));
		this->inputFiringRates[n] = f;
		//printf("Brain::setInput::Calculated Firing Rate for n = %d is %f, dist = %f\n", n, f, position.getSquareDist(neuronMap[n])/2);

	}

}
void Brain::run(float sec, float msec) {
	printf("DEBUG:: running simulation\n");
    if( !poissRate_place ){
    	printf("*Error::Brain::run: possRate_place is NULL\n");
    	return;
    }
	// set the rates and run network
	this->poissRate_place->setRates(this->inputFiringRates);
	//printf("DEBUG:: input size rates = %ld\n", this->inputFiringRates.size());

	this->sm_action_north->startRecording();
	this->sm_action_west->startRecording();
	this->sm_action_east->startRecording();
	this->sm_action_south->startRecording();

	// Check if reward is to be set
	//sim->setLocalRewardModulation(rwEn, cId_place_action, reward, 0.01);

	sim->runNetwork(sec, msec, false);

	this->sm_action_north->stopRecording();
	this->sm_action_west->stopRecording();
	this->sm_action_east->stopRecording();
	this->sm_action_south->stopRecording();

	printf("DEBUG:: end of simulation, out firing rates\n");
}

int Brain::getNumPlaceCells() {
	return this->nPlace;
}
int Brain::getAction() {
	std::vector<float> outRates(nAction);
	outRates[NORTH] = sm_action_north->getPopMeanFiringRate();
	outRates[WEST]  = sm_action_west->getPopMeanFiringRate();
	outRates[EAST]  = sm_action_east->getPopMeanFiringRate();
	outRates[SOUTH] = sm_action_south->getPopMeanFiringRate();
	printf("DEBUG:: Rate[0] = %f, Rate[1] = %f, Rate[2] = %f\n", outRates[0], outRates[1], outRates[2]);
	float max = outRates[0];
	int ret = 0;
	for (int i = 1; i < outRates.size(); i++) {
		if (outRates[i] > max) {
			max = outRates[i];
			ret = i;
		}
	}

	return ret;
}
void Brain::setReward(bool en, float rw) {
	this->rwEn = en;

	if (en)
		this->reward = rw; // weight change modulated by reward
	else
		this->reward = 0.0; // No weight change

}
void Brain::setReward(bool en, float rw, int neurToRw) {
	this->rwEn = en;

	if (en) {
		this->reward = rw; // weight change modulated by reward
		this->neuronToReward = neurToRw;
	} else {
		this->reward = 0.0; // No weight change
		this->neuronToReward = neurToRw;
	}

//	// call reward function of sim here itself
//	if (sim && en) {
//		int actualNeuronId = sim->getGroupStartNeuronId(gAction)
//				+ neuronToReward;
//		sim->setGlobalRewardModulation(true, this->gAction, actualNeuronId,
//				reward, 0);
//	}
}

void Brain::setLocalReward(bool en, float rw, int ActionToRw) {
	this->rwEn = en;

	if (en) {
		this->reward = rw; // weight change modulated by reward
		this->neuronToReward = ActionToRw;
	} else {
		this->reward = 0.0; // No weight change
		this->neuronToReward = ActionToRw;
	}

//	// call reward function of sim here itself
//	if (sim && en) {
//		int actualNeuronId = sim->getGroupStartNeuronId(gAction)
//				+ neuronToReward;
//		sim->setGlobalRewardModulation(true, this->gAction, actualNeuronId,
//				reward, 0);
//	}

	sim->setLocalRewardModulation(en, this->cId_place_action[ActionToRw], rw, 1.0);
}

void Brain::printActionRates() {
		printf("Action Firing Rate [%d] NORTH = %f\n", NORTH,this->sm_action_north->getPopMeanFiringRate());
		printf("Action Firing Rate [%d] WEST = %f\n", WEST,this->sm_action_west->getPopMeanFiringRate());
		printf("Action Firing Rate [%d] EAST = %f\n", EAST,this->sm_action_east->getPopMeanFiringRate());
		printf("Action Firing Rate [%d] SOUTH = %f\n", SOUTH,this->sm_action_south->getPopMeanFiringRate());
}
void Brain::setDAReward(float quota, int ActionToRw){
	switch(ActionToRw){
	case NORTH:
		iSpikeGenDANORTH->setQuotaAll(quota);
		break;
	case SOUTH:
		iSpikeGenDASOUTH->setQuotaAll(quota);
		break;
	case EAST:
		iSpikeGenDAEAST->setQuotaAll(quota);
		break;
	case WEST:
		iSpikeGenDAWEST->setQuotaAll(quota);
		break;
	default:
		break;
	}
}
