/**
 * \file Director.cpp
 * \date Mar 22, 2010
 * \author samael
 */

#include <deque>
#include <iostream>
#include <HelperMacros.h>
#include "Director.h"
#include "Channel.h"
#include "RunnerAgent.h"

using namespace std;

namespace wfe
{

/**
 * Add an actor into the director to execute.
 *
 * \return
 * True on success, false if it already exists inside the director.
 */
bool Director::addActor(AbstractActor *actor)
{
	if (dynamic_cast<AbstractWorkerActor *>(actor)) {
		PERR("Worker actors are not supposed to be added into the Director.");
		return false;
	}
	vector<AbstractActor *>::iterator iter;
	for (iter = _actors.begin(); iter != _actors.end(); iter++) {
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
bool Director::removeActor(AbstractActor *actor)
{
	vector<AbstractActor *>::iterator iter;
	for (iter = _actors.begin(); iter != _actors.end(); iter++) {
		if (*iter == actor) {
			_actors.erase(iter);
			return true;
		}
	}
	return false;
}

/**
 * Create a channel with given name. If the channel already exists, it returns
 * the original one rather than create a new one.
 */
Channel* Director::createChannel(const string &name)
{
	Channel *c;
	if ((c = findChannel(name)))
		return c;

	c = new Channel(name);
	_channels.push_back(c);
	return c;
}

/**
 * Find a channel with given name.
 *
 * \return
 * Proper channel or NULL if nothing found.
 */
Channel* Director::findChannel(const string &name)
{
	for (int i = 0; i < (int)_channels.size(); i++)
		if (_channels[i]->name() == name)
			return _channels[i];
	return NULL;
}

void Director::execute()
{
	PINFO("Executing the actors.");
	_exest->execute(_actors);
}

void Director::execute(uint16_t runner_port, uint16_t master_port,
		const string &name)
{
	if (!RunnerAgent::instance()->setup(runner_port, master_port, name)) {
		PERR("Unable to setup RunnerAgent.");
		return;
	}
	_exest->execute(_actors);
	if (!RunnerAgent::instance()->shutdown()) {
		PERR("Shutdown failed.");
	}
}

}
