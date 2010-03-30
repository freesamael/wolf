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

class Channel;
class Director
{
public:
	Director(IExecutionStrategy *exest): _exest(exest){}
	~Director();
	bool addActor(IActor *actor);
	bool removeActor(IActor *actor);
	Channel* createChannel(const std::string &name);
	Channel* findChannel(const std::string &name);
	void execute();

private:
	std::vector<IActor *> _actors;
	std::vector<Channel *> _channels;
	IExecutionStrategy *_exest;
};

}

#endif /* DIRECTOR_H_ */
