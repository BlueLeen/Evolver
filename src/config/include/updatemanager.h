/*
 * UpdateManager.h
 *
 *  Created on: Sep 18, 2016
 *      Author: su
 */

#ifndef CONFIGURE_UPDATEMANAGER_H_
#define CONFIGURE_UPDATEMANAGER_H_

#include "common_lib/UThread.h"
//#include "common_lib/UThread.h"

class UpdateManager: public UThread {
public:
	UpdateManager(Priority priority = kPNormal);
	virtual ~UpdateManager();
	virtual void mainLoop();
};

#endif /* UPDATEMANAGER_H_ */
