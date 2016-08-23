/*
 * Author: Jessica Gomez <jessica.gomez.hernandez@intel.com>
 * Copyright (c) 2015 - 2016 Intel Corporation.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * @file
 * @ingroup basic
 * @brief On board LED blink C++
 *
 * Blink the on board LED by writing a digital value to an output pin
 * using the IO mraa library.
 *
 * @date 29/09/2015
 */

#include "mraa.hpp"
#include "grove.hpp"

#include <iostream>
#include <unistd.h>
#include "Display.h"
#include "YoNotifier.h"
#include "ldt0028.hpp"
#include <sstream>
#include <time.h>

#define YO_API_KEY "aa27b4f7-dbf6-4abe-b72c-75cf2881d30d"
#define YO_TARGET "GILBERTOMY"

#define TEMP_REFRESH_INTERVAL 5
#define TEMP_NOTIFICATION_INTERVAL 30*60
#define MOVE_INTERVAL 5*60


/*
 * On board LED blink C++ example
 *
 * Demonstrate how to blink the on board LED, writing a digital value to an
 * output pin using the MRAA library.
 * No external hardware is needed.
 *
 * - digital out: on board LED
 *
 * Additional linker flags: none
 */

int main()
{
	Display* display = new Display();

	upm::LDT0028* sensor = new upm::LDT0028(3);

	upm::GroveTemp* temp = new upm::GroveTemp(0);

	YoNotifier* Notifier = new YoNotifier(YO_API_KEY, YO_TARGET);

	float tempValue = 0;
	time_t last_notification_temp = 0;
	time_t last_refresh_temp = 0;
	time_t last_move = 0;
	time_t now;
	float diff;


	for (;;) {

		now = time(0);
		diff = difftime(now, last_refresh_temp);


		if(diff > TEMP_REFRESH_INTERVAL){
			tempValue = temp->value();
			display->setVal(tempValue);
			last_refresh_temp = now;

			diff = difftime(now, last_notification_temp);

			if(diff > TEMP_NOTIFICATION_INTERVAL){
				std::stringstream message;
				message << "Current Temperature: " << tempValue << " Cº";
				Notifier->notify(message.str());
				last_notification_temp = now;

			}
		}


		diff = difftime(now, last_move);

		if(diff > MOVE_INTERVAL){

			if(sensor->getSample() > 100){

				last_move = now;
				display->addOpen();

				std::stringstream message;
				Notifier->notify("Someone has opened the door.");

			}


		}




	}

	return mraa::SUCCESS;
}
