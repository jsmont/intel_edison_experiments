/*
 * Display.cpp
 *
 *  Created on: Aug 21, 2016
 *      Author: j
 */

#include "Display.h"
#include <sstream>

Display::Display() {

	lcd = new upm::Jhd1313m1(0);
	lcd->setColor(255,0,255);

	openCount = 0;
	value = 0;

	refreshView();

}

Display::~Display() {
	// TODO Auto-generated destructor stub
}

void Display::refreshView(){

	lcd->clear();
	lcd->home();

	std::stringstream tempString, timesString;
	tempString << "Temp: " << value << " C";
	timesString << "T: " << openCount;

	lcd->write(tempString.str());
	lcd->setCursor(1,0);
	lcd->write(timesString.str());

}

void Display::addOpen(){
	openCount++;
	refreshView();
}

void Display::setVal(float val){

	value = val;
	refreshView();

}


