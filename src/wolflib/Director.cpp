/*
 * Director.cpp
 *
 *  Created on: Mar 22, 2010
 *      Author: samael
 */

#include <deque>
#include "Channel.h"
#include "Director.h"
#include "AbstractActor.h"

using namespace std;

namespace wfe
{

Director::~Director()
{
	for (int i = 0; i < (int)_actors.size(); i++) {
		delete _actors[i];
	}
}

/**
 * @brief Add an actor into the director to execute.
 * @return True on success, false if it already exists inside the director.
 * @note Director takes the ownership of actors, and will delete/free them.
 */
bool Director::addActor(AbstractActor *actor)
{
	vector<AbstractActor *>::iterator iter;
	for (iter = _actors.begin(); iter != _actors.end(); iter++) {
		if (*iter == actor)
			return false;
	}
	_actors.push_back(actor);
	return true;
}

/**
 * @brief Remove an actor.
 * @return True on success, false if not found.
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
 * @brief Create a channel with given name. If the channel already exists, it
 * returns the original one rather than create a new one.
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
 * @brief Find a channel with given name.
 * @return Proper channel or NULL if nothing found.
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
	_exest->execute(_actors);
}

}
