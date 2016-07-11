/*
 * Brain.cpp
 *
 *  Created on: Jul 11, 2016
 *      Author: amarnath
 */

#include "Brain.h"

Brain::Brain() {
	// Create Brain Here
	// Hardcoded
	sim = new CARLsim("Brain Controller", CPU_MODE, USER);


}

Brain::~Brain() {
	// TODO Auto-generated destructor stub
}

