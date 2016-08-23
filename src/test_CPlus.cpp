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
