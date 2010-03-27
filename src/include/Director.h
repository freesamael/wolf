/*
 * Director.h
 *
 *  Created on: Mar 22, 2010
 *      Author: samael
 */

#ifndef DIRECTOR_H_
#define DIRECTOR_H_

#include <string>
#include <vector>
#include "IExecutionStrategy.h"

namespace wfe
{

class AbstractActor;
class Channel;
class Director
{
public:
	Director(IExecutionStrategy *exest): _exest(exest){}
	~Director();
	bool addActor(AbstractActor *actor);
	bool removeActor(AbstractActor *actor);
	Channel* createChannel(const std::string &name);
	Channel* findChannel(const std::string &name);
	void execute();

private:
	std::vector<AbstractActor *> _actors;
	std::vector<Channel *> _channels;
	IExecutionStrategy *_exest;
};

}

#endif /* DIRECTOR_H_ */
