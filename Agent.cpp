/*
 * Agent.cpp
 *
 *  Created on: Jul 10, 2016
 *      Author: amarnath
 */

#include "Agent.h"
#include <cstdio>

Agent::Agent(Point ref, Point iP, float iA, int nsens, ALLEGRO_BITMAP* image) {

	this->refOrigin.copy(ref);
	// TODO Auto-generated constructor stub
	this->initialAngle = iA;

	this->currentAngle = iA;

	this->initialPosition.set(iP.x, iP.y);

	this->initialGridPosition.set(0.0, 0.0);

	this->currentPosition.set(iP.x, iP.y);

	this->currentGridPosition.set(0.0, 0.0);

	this->image = image;

	this->width = al_get_bitmap_width(image);

	this->height = al_get_bitmap_height(image);

	this->numOfSensors = nsens;

	this->US = new UltrasonicSensor[nsens];

	this->dSens = ALLEGRO_PI / (nsens - 1);

	this->pBrain = NULL;
	this->pEnv = NULL;
	// initialize sensors
	for (int i = 0; i < nsens; i++) {

		US[i].setIndex(i - nsens / 2);
		US[i].setDSens(dSens);
	}
	this->withTrail = false;
	this->withJump = false;
	this->jumpVelocity.x = 10.;
	this->jumpVelocity.y = 10.;
	this->immReward = 0.;

}

Agent::Agent(Point ref, Point iP, float iA, int nsens, float width,
		float height) {
	// TODO Auto-generated constructor stub
	this->refOrigin.copy(ref);

	this->initialAngle = iA;

	this->currentAngle = iA;

	this->initialPosition.set(iP.x, iP.y);

	this->initialGridPosition.set(0.0, 0.0);

	this->currentPosition.set(iP.x, iP.y);

	this->currentGridPosition.set(0.0, 0.0);

	this->image = image;

	this->width = width;

	this->height = height;

	this->numOfSensors = nsens;

	this->US = new UltrasonicSensor[nsens];

	this->dSens = 3.14 / (nsens - 1);
	this->pBrain = NULL;
	this->pEnv = NULL;

	// initialize sensors
	for (int i = 0; i < nsens; i++) {

		US[i].setIndex(i - nsens / 2);
		US[i].setDSens(dSens);
	}
	this->withTrail = false;
	this->withJump = false;
	this->jumpVelocity.x = 10.;
	this->jumpVelocity.y = 10.;
	this->immReward = 0.;

}

Agent::~Agent() {
	// TODO Auto-generated destructor stub
	delete[] US;
	if (pBrain)
		delete pBrain;
}

void Agent::draw() {

	if (!image) {
		printf("Agent::draw() No Agent Image found to draw\n");
		return;
	}

	//printf("Agent::draw() Called\n");
	// consider frame of reference: refOrigin
	al_draw_rotated_bitmap(image, width / 2, height / 2,
	/*float dx*/refOrigin.x + currentPosition.x, /*float dy*/
	refOrigin.y + currentPosition.y,
	/*float radian angle*/currentAngle,
	/*int flags*/0);

	if (withTrail) {
		std::list<Point>::iterator itr = trail.begin();
		// draw the starting point a little different
		al_draw_filled_circle(refOrigin.x + itr->x, refOrigin.y + itr->y, 5.0,
				al_map_rgb(255, 0, 0));
		itr++;
		while (itr != trail.end()) {

			al_draw_filled_circle(refOrigin.x + itr->x, refOrigin.y + itr->y,
					2.0, al_map_rgb(255, 255, 0));
			itr++;
		}
	}

}

Point Agent::getCurrentPosition() {
	return this->currentPosition;
}
float Agent::getCurrentAngle() {
	return this->currentAngle;
}

void Agent::setEnv(Environment* pEnv) {
	this->pEnv = pEnv;

}

void Agent::updatePosition() {

	if (withTrail)
		this->trail.push_back(currentPosition);

	//printf("Update Position Called:\n");

	float dt = 0.1;

	// activate brain
	if (pBrain)
		if (pBrain->neuronMap.size() != 0) {
			pBrain->setInput(currentPosition);
//			//visualize rates
//			//pEnv->visualizePlaceCellFiring(pBrain->neuronMap, pBrain->inputFiringRates);
//			// Calculate rewards for each action before hand
//			// to be given globally as in Florian XOR
//
			int actionRewarded = this->getCollisionAvoidanceAction();
//			int actionPunished = this->getCollisionSeekingAction();
			printf("Action To be rewarded = "); printAction(actionRewarded);
//			printf("Action To be punished = "); printAction(actionPunished);
			if (actionRewarded != -1)
				pBrain->setDAReward( 100, actionRewarded);
			else
				pBrain->setDAReward(0, 0);
//			// to set punishments
////			if (actionPunished != -1)
////					pBrain->setReward(true, -0.001, actionPunished);
////			else
////					pBrain->setReward(true, 0., 0);
//			//pBrain->setReward(true, 0.5., actionRewarded); // checking ... comment this later
//			//pBrain->setReward(true, 0.5, USNORTH);
			printf("calling run\n");
			pBrain->run(0, 500);
			printf("after run\n");
			pBrain->printActionRates();
//
			switch (pBrain->getAction()) {

			case NORTH:
				printf("Agent::updatePosition:Brain Action %s\n",
						withJump ? "Jump North" : "moveForward");
				withJump ? this->jumpNorth() : this->moveForward(dt);
				break;
			case WEST:
				printf("Agent::updatePosition:Brain Action %s\n",
						withJump ? "Jump West" : "moveLeft");
				withJump ? this->jumpWest() : this->moveLeft(dt);
				break;
			case EAST:
				printf("Agent::updatePosition:Brain Action %s\n",
						withJump ? "Jump East" : "moveRight");
				withJump ? this->jumpEast() : this->moveRight(dt);
				break;
			case SOUTH:
				printf("Agent::updatePositionw:Brain Action %s\n",
						withJump ? "Jump South" : "moveBackward");
				withJump ? this->jumpSouth() : this->moveBackward(dt);
				break;

			default:
				printf("Agent::updatePosition:DEFAULT Action %s\n",
						withJump ? "Jump North" : "moveForward");
				withJump ? this->jumpNorth() : this->moveForward(dt);
				break;
			}
		}

	//this->turnRight(0.01);
	// update Sensor values while drawing them
	if (pEnv) {
		for (int i = 0; i < numOfSensors; i++){
			this->US[i].calcDistance(pEnv, currentPosition, currentAngle);
			printf("US[%d] = %f\n", i, US[i].getDistance());
		}
	}
	immReward = 0.;

	if (hasCollided()) {
		this->currentPosition.copy(this->initialPosition);
		this->currentAngle = 0.0;
		immReward = -100.0;
		printf("*Collided - Immediate Reward = %f *\n", immReward);

	} else {
		if (pEnv->isTarget(currentPosition)) {

			this->currentPosition.copy(this->initialPosition);
			this->currentAngle = 0.0;
			immReward = 1.0;
			printf("*Target Reached - Immediate Reward = %f *\n", immReward);
		}
	}
	// now set reward
	//pBrain->setReward(true, immReward);

	printf("New Position %f, %f \n", currentPosition.x, currentPosition.y);
	draw();

}

void Agent::moveForward(float runTime) {

	printf("Agent::moveForward Called\n");
	this->ML.setRunTime(runTime);
	this->ML.setRPM(200);
	this->ML.setRotationType(FORWARD);
	this->ML.rotateWheel(&WL);

	this->MR.setRunTime(runTime);
	this->MR.setRPM(200);
	this->MR.setRotationType(FORWARD);
	this->MR.rotateWheel(&WR);
	// calculate wheel travel distance here
	// noOfRotations*circumference
	float DLW = (this->WL.getAngleRotated()) * (this->WL.getDiameter()) / 2; // left wheel distance
	float DRW = (this->WR.getAngleRotated()) * (this->WR.getDiameter()) / 2; // right wheel distance

	float dTheta = (DLW - DRW) / this->width;  // rotation about C.O.M

	float dx = 0.5 * (DLW + DRW) * sin(currentAngle);
	float dy = 0.5 * (DLW + DRW) * cos(currentAngle);

	currentPosition.x += dx;
	currentPosition.y -= dy;
	currentAngle += dTheta;

	printf(
			"Agent::moveForward():DLW = %f, DRW = %f, dx = %f, dy = %f, CurrentPosition = %f,%f\n",
			DLW, DRW, dx, dy, currentPosition.x, currentPosition.y);
}

void Agent::moveLeft(float runTime) {
	turnLeft(runTime);
	moveForward(runTime);
}
void Agent::moveRight(float runTime) {
	turnRight(runTime);
	moveForward(runTime);
}
void Agent::moveBackward(float runTime) {
	printf("Agent::moveForward Called\n");
	this->ML.setRunTime(runTime);
	this->ML.setRPM(200);
	this->ML.setRotationType(BACKWARD);
	this->ML.rotateWheel(&WL);

	this->MR.setRunTime(runTime);
	this->MR.setRPM(200);
	this->MR.setRotationType(BACKWARD);
	this->MR.rotateWheel(&WR);
	// calculate wheel travel distance here
	// noOfRotations*circumference
	float DLW = (this->WL.getAngleRotated()) * (this->WL.getDiameter()) / 2; // left wheel distance
	float DRW = (this->WR.getAngleRotated()) * (this->WR.getDiameter()) / 2; // right wheel distance

	float dTheta = (DLW - DRW) / this->width;  // rotation about C.O.M

	float dx = 0.5 * (DLW + DRW) * sin(currentAngle);
	float dy = 0.5 * (DLW + DRW) * cos(currentAngle);

	currentPosition.x += dx;
	currentPosition.y -= dy;
	currentAngle += dTheta;

	printf(
			"Agent::moveBackward():DLW = %f, DRW = %f, dx = %f, dy = %f, CurrentPosition = %f,%f\n",
			DLW, DRW, dx, dy, currentPosition.x, currentPosition.y);
}
void Agent::turnLeft(float runTime) {
	printf("Agent::turnLeft Called\n");
	this->ML.setRunTime(runTime);
	this->ML.setRPM(200);
	this->ML.setRotationType(BACKWARD);
	this->ML.rotateWheel(&WL);

	this->MR.setRunTime(runTime);
	this->MR.setRPM(1200);
	this->MR.setRotationType(FORWARD);
	this->MR.rotateWheel(&WR);
	// calculate wheel travel distance here
	// noOfRotations*circumference
	float DLW = (this->WL.getAngleRotated()) * (this->WL.getDiameter()) / 2; // left wheel distance
	float DRW = (this->WR.getAngleRotated()) * (this->WR.getDiameter()) / 2; // right wheel distance

	float dTheta = (DLW - DRW) / this->width;  // rotation about C.O.M

	float dx = 0.5 * (DLW + DRW) * sin(currentAngle);
	float dy = 0.5 * (DLW + DRW) * cos(currentAngle);

	currentPosition.x += dx;
	currentPosition.y -= dy;
	currentAngle += dTheta;
}
void Agent::turnRight(float runTime) {
	printf("Agent::turnRight Called\n");
	this->ML.setRunTime(runTime);
	this->ML.setRPM(200);
	this->ML.setRotationType(FORWARD);
	this->ML.rotateWheel(&WL);

	this->MR.setRunTime(runTime);
	this->MR.setRPM(1200);
	this->MR.setRotationType(BACKWARD);
	this->MR.rotateWheel(&WR);
	// calculate wheel travel distance here
	// noOfRotations*circumference
	float DLW = (this->WL.getAngleRotated()) * (this->WL.getDiameter()) / 2; // left wheel distance
	float DRW = (this->WR.getAngleRotated()) * (this->WR.getDiameter()) / 2; // right wheel distance

	float dTheta = (DLW - DRW) / this->width;  // rotation about C.O.M

	float dx = 0.5 * (DLW + DRW) * sin(currentAngle);
	float dy = 0.5 * (DLW + DRW) * cos(currentAngle);

	currentPosition.x += dx;
	currentPosition.y -= dy;
	currentAngle += dTheta;
}
void Agent::setTrail(bool tr) {
	this->withTrail = tr;
}
bool Agent::hasCollided() {
	for (int i = 0; i < this->numOfSensors; i++) {
		if (US[i].getDistance() < width) {
			return true;
		}
	}

	return false;
}

void Agent::setBrain(Brain* br) {
	if (br) {
		this->pBrain = br;
	}
}
void Agent::mapPlaceCells() {

	if (!pBrain) {
		printf("*Agent::mapPlaceCells- No brain found\n");
		return;
	}

	if (!pEnv) {

		printf("*Agent::mapPlaceCells- No Environment Pointer found\n");
		return;
	}

	if (!(pEnv->hasGrid())) {
		printf("*Agent::mapPlaceCells- Env has No grid, Please enable it\n");
		return;
	}
	// for each grid location, get its actual co-ordinates in pixels
	int cols = pEnv->width / pEnv->slotSize;
	int rows = pEnv->height / pEnv->slotSize;

	if (cols * rows != pBrain->getNumPlaceCells()) {
		printf(
				"*Agent::mapPlaceCells-rows and columns inconsistent with place cell number\n");
		return;
	}

	for (int c = 0; c < cols; c++) {
		for (int r = 0; r < rows; r++) {
			// get actual co-ordinates
			Point p = pEnv->getGridSlotCenter(c, r);
			//printf("c=%d, r = %d, P = ",c,r);
			//p.print();
			pBrain->neuronMap.push_back(p);
			//pBrain->neuronMap[0].print();
		}
	}

}

// Jump functions are idealistic now
// need to be implemented in a realistic way
// using motors and motor runtime
void Agent::jumpNorth() {

	this->currentPosition.y -= this->jumpVelocity.y;

}
void Agent::jumpWest() {

	this->currentPosition.x -= this->jumpVelocity.x;
}
void Agent::jumpEast() {

	this->currentPosition.x += this->jumpVelocity.x;
}
void Agent::jumpSouth() {
	this->currentPosition.y += this->jumpVelocity.y;
}

void Agent::setJump(bool en, float Vx, float Vy) {
	this->withJump = en;
	if (en) {
		this->jumpVelocity.x = Vx;
		this->jumpVelocity.y = Vy;
	}

}
int Agent::getCollisionAvoidanceAction() {
	// Check if current position has close obstacle on left
	if (US[USLEFT].getDistance() < width) {
		return EAST;
	}
	if (US[USRIGHT].getDistance() < width) {
		return WEST;
	}
	if (US[USFRONT].getDistance() < width) {
		return SOUTH;
	}
	// check southwards
	if( pEnv->isInvalid( Point(currentPosition.x, currentPosition.y + 20) ) ) {
		return NORTH;
	}
	return -1; // no particular action -let it be random
}

int Agent::getCollisionSeekingAction() {
	// Check if current position has close obstacle on left
	if (US[USLEFT].getDistance() < width) {
		return WEST;
	}
	if (US[USRIGHT].getDistance() < width) {
		return EAST;
	}
	if (US[USFRONT].getDistance() < width) {
		return NORTH;
	}
	return -1; // no particular action -let it be random
}

void Agent::printAction(int action) {

	switch (action) {
	case NORTH:
		printf("NORTH\n");
		break;
	case WEST:
		printf("WEST\n");
		break;
	case EAST:
		printf("EAST\n");
		break;
	case SOUTH:
		printf("SOUTH\n");
		break;
	default:
		printf("DEFAULT\n");
		break;
	}
}
