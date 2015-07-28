/**
 * \file CDirector.cpp
 * \date Mar 22, 2010
 * \author samael
 */

#include "CDirector.h"

#include <deque>
#include <iostream>
#include <sstream>
#include "HelperMacros.h"
#include "CChannel.h"
#include "CMaster.h"

using namespace std;

namespace wolf
{

CDirector::~CDirector()
{
	for (unsigned i = 0; i < _channels.size(); i++)
		delete _channels[i];
}

/**
 * Add an actor into the director to execute.
 *
 * \return
 * True on success, false if it already exists inside the director.
 */
bool CDirector::addActor(AActor *actor)
{
	if (dynamic_cast<AWorkerActor *>(actor)) {
		PERR("Worker actors are not supposed to be added into the Director.");
		return false;
	}
	vector<AActor *>::iterator iter;
	for (iter = _actors.begin(); iter != _actors.end(); ++iter) {
		if (*iter == actor)
			return false;
	}
	_actors.push_back(actor);
	return true;
}

/**
 * Remove an actor.
 *
 * \return
 * True on success, false if not found.
 */
bool CDirector::removeActor(AActor *actor)
{
	vector<AActor *>::iterator iter;
	for (iter = _actors.begin(); iter != _actors.end(); ++iter) {
		if (*iter == actor) {
			_actors.erase(iter);
			return true;
		}
	}
	return false;
}

/**
 * Create a channel.
 */
CChannel* CDirector::createChannel()
{
	CChannel *c;
	c = new CChannel();
	_channels.push_back(c);
	return c;
}

void CDirector::execute()
{
	_exest->execute(_actors);
}

void CDirector::execute(in_port_t runner_port, in_port_t master_port,
		const string &name)
{
	if (!CMaster::instance()->setup(runner_port, master_port, name)) {
		PERR("Unable to setup Master.");
		return;
	}
	_exest->execute(_actors);
	CMaster::instance()->shutdown();
}

}
