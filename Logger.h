/*
 * Logger.h
 *
 *  Created on: 21 Dec 2013
 *      Author: bert
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <log4cpp/Category.hh>
#include <log4cpp/PropertyConfigurator.hh>

class Logger {
public:
	Logger();
	virtual ~Logger();

	static log4cpp::Category* GetLogger();

public:
	static log4cpp::Category* root;
};

#endif /* LOGGER_H_ */
