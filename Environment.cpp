/*
 * Environment.cpp
 *
 *  Created on: Jul 10, 2016
 *      Author: amarnath
 */

#include "Environment.h"

#include <cstdio>
Environment::Environment(int w, int h, int dw, int dh) {
	// TODO Auto-generated constructor stub
	this->width = w;
	this->height = h;
	this->dispHeight = dh;
	this->dispWidth = dw;
	this->slotSize = 50;
	this->withGrid = false;

}

Environment::~Environment() {
	// TODO Auto-generated destructor stub
}

void Environment::setObstacle(Point p, int w, int h) {
	Obstacle obs;
	int woffset = dispWidth - width;
	int hoffset = dispHeight - height;

	obs.tlc.set(woffset + p.x, hoffset + p.y);
	obs.width = w;
	obs.height = h;

	obstacles.push_back(obs);

}

void Environment::setTarget(Point p, int w, int h) {
	Obstacle tgt;
	int woffset = dispWidth - width;
	int hoffset = dispHeight - height;

	tgt.tlc.set(woffset + p.x, hoffset + p.y);
	tgt.width = w;
	tgt.height = h;

	targets.push_back(tgt);

}

void Environment::draw() {

	// Check if Allegro Env is Initialized
	if (!al_init()) {
		printf(
				"Error: Environment::draw() : Allegro Environment Not Initialized Yet\n");
		return;
	}

	// Draw if Allegro Display exists
	if (obstacles.size()) {
		std::list<Obstacle>::iterator itr = obstacles.begin();
		while (itr != obstacles.end()) {
			//printf("obstacle draw called\n");
			al_draw_filled_rectangle(itr->tlc.x, itr->tlc.y,
					itr->tlc.x + itr->width, itr->tlc.y + itr->height,
					al_map_rgb(255, 255, 255));
			itr++;
		}
	}

	if (targets.size()) {
		std::list<Obstacle>::iterator itr1 = targets.begin();
		while (itr1 != targets.end()) {
			//printf("obstacle draw called\n");
			al_draw_filled_rectangle(itr1->tlc.x, itr1->tlc.y,
					itr1->tlc.x + itr1->width, itr1->tlc.y + itr1->height,
					al_map_rgb(0, 255, 0));
			itr1++;
		}
	}
	if (withGrid) {
		drawGrid(true);
	}

}

Point Environment::getGridSlotCenter(int x, int y) {

	if (!withGrid) {
		printf(
				"Environment::getGridSlotCenter: do 'setGrid(enable, slotSize)' to enable grid operations\n");
		return Point(-1, -1);
	}

	//bottom left
	float bly = dispHeight; //height - ((height - rows*slotSize) / 2 );
	float blx = dispWidth - width; //(width  - columns*slotSize) / 2 ;
	// calculate offset
	Point P(0, 0);
	P.x = blx + x * slotSize + (slotSize / 2);
//	P.y = bly - ((rows - y - 1)*slotSize + ( slotSize / 2 ));
	P.y = bly - ((y) * slotSize + (slotSize / 2));
	return P;
}

void Environment::setGrid(bool enable, int slotSize) {
	this->withGrid = enable;
	if (enable) {
		this->slotSize = slotSize;
	}
}

void Environment::drawGrid(bool showCenter) {

	if (!withGrid) {
		printf(
				"Environment::drawGrid(): do setGrid(true,<slotSize>) to perform grid operations\n");
	}
	// calculate rows and columns of the grid
	int rows = height / slotSize;
	int columns = width / slotSize;

	// top left corner of the grid
	float y = dispHeight - height; // (displayHeight - rows*slotSize) / 2 ;
	float x = dispWidth - width; // (displayWidth  - columns*slotSize) / 2 ;

	int line_size = 3;
	al_draw_rectangle(x, y, x + columns * slotSize, y + rows * slotSize,
			al_map_rgb(0, 255, 0), 5);

	// vertical lines
	for (int i = 1; i <= columns - 1; i++) {
		al_draw_line(x + i * slotSize, y, x + i * slotSize, y + rows * slotSize,
				al_map_rgb(0, 255, 0), line_size);
	}

	// horizontal lines
	for (int i = 1; i <= rows - 1; i++) {
		al_draw_line(x, y + i * slotSize, x + columns * slotSize,
				y + i * slotSize, al_map_rgb(0, 255, 0), line_size);
	}

	if (showCenter) {
		ALLEGRO_FONT* font = al_load_font("arial.ttf", 12, 0);
		if (!font) {
			printf("Environment::drawGrid(): font couldn't be loaded\n");
			return;
		}
		// find slot centre for each row and column
		// and add text there
		for (int i = 0; i < columns; i++) {
			for (int j = 0; j < rows; j++) {
				Point p = getGridSlotCenter(i, j);
				//al_draw_filled_circle(p.x, p.y, 5.0, al_map_rgb(255, 0, 0));
				al_draw_textf(font, al_map_rgb(255, 255, 255), p.x, p.y,
						ALLEGRO_ALIGN_CENTER, "%d,%d", i, j);
			}
		}

		al_destroy_font(font);
	}
	/*
	 //draw slant lines in each slot
	 for(int i = 0; i < rows; i++){
	 for(int j = 0; j < columns; j++){


	 if(!is_obstacle(j, rows - i - 1) && ( (j != target.x) || ((rows - i - 1) != target.y) ) ){
	 // draw leftward slant lines
	 al_draw_line(x + j*slotSize,y + i*slotSize, x + (j+1)*slotSize, y + (i+1)*slotSize,
	 al_map_rgb(255,255,255),line_size);


	 // draw rightward slant lines
	 al_draw_line(x + j*slotSize, y + (i+1)*slotSize, x + (j+1)*slotSize, y + (i)*slotSize,
	 al_map_rgb(255,255,255),line_size);


	 }
	 }

	 }
	 */
}

Point Environment::getContainingSlotCenter(Point P) {
	// Point is assumed with respect to

	return Point(-1, -1);
}

bool Environment::hasGrid() {
	return withGrid;
}
bool Environment::isTarget(Point pos) {
	// check if reached target
	for (std::list<Obstacle>::iterator itr = targets.begin();
			itr != targets.end(); itr++) {

		if (itr->hasPoint(pos.x, pos.y)) {
			return true;
		}
	}

	return false;
}
