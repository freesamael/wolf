/**
 * \file Director.cpp
 * \date Mar 22, 2010
 * \author samael
 */

#include <deque>
#include <iostream>
#include <sstream>
#include "HelperMacros.h"
#include "Director.h"
#include "Channel.h"
#include "Master.h"

using namespace std;

namespace wfe
{

Director::~Director()
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
bool Director::addActor(AbstractActor *actor)
{
	if (dynamic_cast<AbstractWorkerActor *>(actor)) {
		PERR("Worker actors are not supposed to be added into the Director.");
		return false;
	}
	vector<AbstractActor *>::iterator iter;
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
bool Director::removeActor(AbstractActor *actor)
{
	vector<AbstractActor *>::iterator iter;
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
Channel* Director::createChannel()
{
	Channel *c;
	c = new Channel();
	_channels.push_back(c);
	return c;
}

void Director::execute()
{
	PINF_2("Executing the actors.");
	_exest->execute(_actors);
}

void Director::execute(uint16_t runner_port, uint16_t master_port,
		const string &name)
{
	if (!Master::instance()->setup(runner_port, master_port, name)) {
		PERR("Unable to setup Master.");
		return;
	}
	_exest->execute(_actors);
	Master::instance()->shutdown();
}

}
