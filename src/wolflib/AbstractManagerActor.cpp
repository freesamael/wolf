/*
 * AbstractManagerActor.cpp
 *
 *  Created on: Mar 28, 2010
 *      Author: samael
 */

#include "AbstractManagerActor.h"
#include "Port.h"
#include "Channel.h"

namespace wfe
{

/**
 * \note
 * AbstractManagerActor deletes all ports on destruction.
 */
AbstractManagerActor::~AbstractManagerActor()
{
	for (int i = 0; i < (int)_inports.size(); i++)
		delete _inports[i];

	for (int i = 0; i < (int)_outports.size(); i++)
		delete _outports[i];
}

/**
 * By default it executes all workers by the executor given during construction.
 */
void AbstractManagerActor::fire()
{
	if (_exec)
		_exec->execute(_workers);
}

/**
 * Test if all inputs are ready.
 *
 * \return
 * True if all inputs are ready or there's no inputs. False otherwise.
 */
bool AbstractManagerActor::isInputReady() const
{
	for (int i = 0; i < (int)_inports.size(); i++) {
		if (!_inports[i]->channel())
			return false;
		if (_inports[i]->channel()->state() != Channel::WRITTEN)
			return false;
	}
	return true;
}

}
