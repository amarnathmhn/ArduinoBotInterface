/*
 * Brain.cpp
 *
 *  Created on: Jul 11, 2016
 *      Author: amarnath
 */

#include "Brain.h"

Brain::Brain() {

	sim = new CARLsim("Brain Controller", CPU_MODE, USER);

}

Brain::~Brain() {
	// TODO Auto-generated destructor stub
	if (sim)
		delete sim;
	if (poissRate_place)
		delete poissRate_place;
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
	// Create Brain Here
	// Hardcoded Izhikevich Neurons
	this->nPlace = nPlace;   // 10x10 grid of 100 Neurons
	this->nAction = nAction;    // 3 Action Neurons

	if( !sim ) {
		printf("Brain::createHippocampal: failed because sim is NULL\n");
	}
	this->gPlace = sim->createSpikeGeneratorGroup("PlaceCells",
			Grid3D(10, 10, 0), EXCITATORY_NEURON);
	this->gAction = sim->createGroup("Action", nAction, EXCITATORY_NEURON);

	this->cId_place_action = sim->connect(gPlace, gAction, "full",
			RangeWeight(0, 0.1, 5.0), 1.0f, RangeDelay(1.0f), RadiusRF(-1),
			SYN_PLASTIC);

	sim->setWeightAndWeightChangeUpdate(INTERVAL_10MS, true, 0.90f);

	stdpType_t stdpType = DA_MOD;
	sim->setESTDP(gAction, true, stdpType, ExpCurve(0.001, 20.0, -0.015, 20.0));
	sim->setConductances(true);
	sim->setupNetwork();

	//******************************* CREATE MONITORS **********************************************//
	this->cm_place_action = sim->setConnectionMonitor(gPlace, gAction,
			"DEFAULT");
	this->sm_action = sim->setSpikeMonitor(gAction, "DEFAULT");

	srand(static_cast<unsigned>(time(0)));
	setRandomWeights(cm_place_action, 0, 5);

	this->poissRate_place = new PoissonRate(nPlace);
	sim->setSpikeRate(gPlace, poissRate_place);
}

