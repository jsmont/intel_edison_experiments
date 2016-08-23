/*
 * Display.h
 *
 *  Created on: Aug 21, 2016
 *      Author: j
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <jhd1313m1.hpp>

class Display {
private:
	upm::Jhd1313m1* lcd;
	int openCount;
	float value;

	void refreshView();

public:
	Display();
	virtual ~Display();
	void addOpen();
	void setVal(float val);
};

#endif /* DISPLAY_H_ */
