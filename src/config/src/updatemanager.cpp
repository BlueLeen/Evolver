/*
 * UpdateManager.cpp
 *
 *  Created on: Sep 18, 2016
 *      Author: su
 */

#include "updatemanager.h"
#include <unistd.h>
#include "common.h"
#include "nodevent.h"

extern NodEvent* g_umNodeCfg[UPGRADE];

UpdateManager::UpdateManager(Priority priority) {
	// TODO Auto-generated constructor stub

}

UpdateManager::~UpdateManager() {
	// TODO Auto-generated destructor stub
}

void UpdateManager::mainLoop()
{
	for(int i=0; i<UPGRADE; i++)
	{
		if(g_umNodeCfg[i]->getUpdate())
		{
			g_umNodeCfg[i]->notify();
			g_umNodeCfg[i]->setUpdate(false);
		}
	}
	usleep(10);
}

