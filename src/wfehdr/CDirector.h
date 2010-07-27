/**
 * \file CDirector.h
 * \date Mar 22, 2010
 * \author samael
 */

#ifndef CDIRECTOR_H_
#define CDIRECTOR_H_

#include <string>
#include <vector>
#include <netinet/in.h>
#include "HelperMacros.h"
#include "IWorkflowExecutor.h"

namespace wolf
{

class CChannel;
class CDirector
{
public:
	CDirector(IWorkflowExecutor *exest): _actors(), _channels(), _exest(exest){}
	~CDirector();
	bool addActor(AActor *actor);
	bool removeActor(AActor *actor);
	CChannel* createChannel();
	std::vector<CChannel *>& channels() { return _channels; }
	void execute();
	void execute(in_port_t runner_port, in_port_t master_port,
			const std::string &name = "default");

private:
	CDirector(const CDirector &UNUSED(o)): _actors(), _channels(), _exest(NULL) {}
	CDirector& operator=(const CDirector &UNUSED(o)) { return *this; }
	std::vector<AActor *> _actors;
	std::vector<CChannel *> _channels;
	IWorkflowExecutor *_exest;
};

}

#endif /* CDIRECTOR_H_ */
