/**
 * \file Director.h
 * \date Mar 22, 2010
 * \author samael
 */

#ifndef DIRECTOR_H_
#define DIRECTOR_H_

#include <string>
#include <vector>
#include "IWorkflowExecutor.h"

namespace wfe
{

class Channel;
class Director
{
public:
	Director(IWorkflowExecutor *exest): _exest(exest){}
	~Director();
	bool addActor(AbstractActor *actor);
	bool removeActor(AbstractActor *actor);
	Channel* createChannel(const std::string &name);
	Channel* findChannel(const std::string &name);
	void execute();
	void execute(unsigned short runner_port, unsigned short master_port,
			const std::string &name);

private:
	std::vector<AbstractActor *> _actors;
	std::vector<Channel *> _channels;
	IWorkflowExecutor *_exest;
};

}

#endif /* DIRECTOR_H_ */
