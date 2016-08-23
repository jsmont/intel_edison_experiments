/*
 * Notifier.h
 *
 *  Created on: Aug 21, 2016
 *      Author: j
 */

#ifndef NOTIFIER_H_
#define NOTIFIER_H_


#include <iostream>
#include <unistd.h>
#include <string>


class YoNotifier {
private:

	std::string api_key;
	std::string username;
	std::string YO_API_URL;

public:
	YoNotifier(std::string api_key, std::string username);
	virtual ~YoNotifier();
	void notify(std::string message);
};

#endif /* NOTIFIER_H_ */
