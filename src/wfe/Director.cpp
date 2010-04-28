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

Director::~Director()
{
	for (unsigned i = 0; i < _channels.size(); i++)
		delete _channels[i];
}

/**
 * Nothing can stop you to copy contruct a Directory. However, it's very usual
 * and they share the same executor, so be careful of the lifetime.
 */
Director::Director(const Director &dir):
		_actors(dir._actors), _channels(), _exest(dir._exest)
{
	for (unsigned i = 0; i < dir._channels.size(); i++)
		createChannel(dir._channels[i]->name());
}

/**
 * Assignment. It duplicates all channels from assigner by creating channels
 * with the same name.
 */
Director& Director::operator=(const Director &dir)
{
	_actors = dir._actors;
	_exest = dir._exest;

	// Clear old channels and duplicate channels from assigner.
	for (unsigned i = 0; i < _channels.size(); i++)
		delete _channels[i];
	_channels.clear();
	for (unsigned i = 0; i < dir._channels.size(); i++)
		createChannel(dir._channels[i]->name());
	return *this;
}

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
	for (unsigned i = 0; i < _channels.size(); i++)
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
	if (!Master::instance()->setup(runner_port, master_port, name)) {
		PERR("Unable to setup RunnerAgent.");
		return;
	}
	_exest->execute(_actors);
	if (!Master::instance()->shutdown()) {
		PERR("Shutdown failed.");
	}
}

}
