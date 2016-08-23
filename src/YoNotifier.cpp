/*
 * Notifier.cpp
 *
 *  Created on: Aug 21, 2016
 *      Author: j
 */

#include "YoNotifier.h"
#include <stdlib.h>
#include <iostream>
#include <string>

YoNotifier::YoNotifier(std::string api_key, std::string username) {

	this->api_key = api_key;
	this->username = username;
	this->YO_API_URL="http://api.justyo.co/yo/";

}

YoNotifier::~YoNotifier() {
	// TODO Auto-generated destructor stub
}

void YoNotifier::notify(std::string message){
	std::string call = "curl " + YO_API_URL + " -XPOST --data \"api_token="+ api_key +"&username="+username+"&text="+message+"\"";
	system(call.c_str());
}

