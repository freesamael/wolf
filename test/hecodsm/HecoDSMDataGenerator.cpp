/**
 * \file HecoDSMDataGenerator.cpp
 * \date Apr 15, 2010
 * \author samael
 */

#include <iostream>
#include <sstream>
#include <HelperMacros.h>
#include <cstdio>
#include <cstring>
#include <CD2mce.h>
#include <CSharedMemory.h>
#include "HecoDSMDataGenerator.h"

using namespace wfe;

void HecoDSMDataGenerator::prefire()
{
	_state = RUNNING;
	_item = D2MCE::instance()->createSharedMemory(4 * sizeof(int));
}

void HecoDSMDataGenerator::fire()
{
	_item->lock();
	memset(_item->buffer(), 0, 4 * sizeof(int));
	_item->store();
	_item->unlock();

	int *num = (int *)_item->buffer();
	PINF_1("Num = " << num[0] << " " << num[1] << " " <<  num[2] << " " <<
			num[3]);

	_state = POST_RUNNING;
}

void HecoDSMDataGenerator::postfire()
{
	sourcePorts()[0]->writeChannel(_item);
	_state = FINISHED;
}
