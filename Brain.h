/*
 * Brain.h
 *
 *  Created on: Jul 11, 2016
 *      Author: amarnath
 */

#ifndef BRAIN_H_
#define BRAIN_H_

#include "carlsim.h"

class Brain {

private: CARLsim* sim;
public:
	Brain();
	virtual ~Brain();
};

#endif /* BRAIN_H_ */
