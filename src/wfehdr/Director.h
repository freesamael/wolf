/**
 * \file Director.h
 * \date Mar 22, 2010
 * \author samael
 */

#ifndef DIRECTOR_H_
#define DIRECTOR_H_

#include <string>
#include <vector>
#include <stdint.h>
#include "HelperMacros.h"
#include "IWorkflowExecutor.h"

namespace wfe
{

class Channel;
class Director
{
public:
	Director(IWorkflowExecutor *exest): _actors(), _channels(), _exest(exest){}
	~Director();
	bool addActor(AbstractActor *actor);
	bool removeActor(AbstractActor *actor);
	Channel* createChannel();
	std::vector<Channel *>& channels() { return _channels; }
	void execute();
	void execute(uint16_t runner_port, uint16_t master_port,
			const std::string &name = "default");

private:
	Director(const Director &UNUSED(o)): _actors(), _channels(), _exest(NULL) {}
	Director& operator=(const Director &UNUSED(o)) { return *this; }
	std::vector<AbstractActor *> _actors;
	std::vector<Channel *> _channels;
	IWorkflowExecutor *_exest;
};

}

#endif /* DIRECTOR_H_ */
