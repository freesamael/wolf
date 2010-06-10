/**
 * \file Master.h
 * \date Apr 1, 2010
 * \author samael
 */

#ifndef MASTER_H_
#define MASTER_H_

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "TCPSocket.h"
#include "HelperMacros.h"
#include "AbstractWorkerActor.h"
#include "SimpleWorkerDispatcher.h"

namespace wfe
{

struct PData;

/**
 * Master plays the middle man between runners and workflow executors.
 */
class Master
{
	SINGLETON(Master);
public:
	typedef enum State {
		NOT_READY,
		READY,
		END
	} State;
	static const std::string StateString[];

	inline State state() const { return _state; }
//	inline const std::vector<cml::TCPSocket *>& runners() const
//			{ return _runnersocks; }
	inline IWorkerDispatcher* dispatcher() const { return _activedisp; }
	inline void setDispatcher(IWorkerDispatcher *d) { _activedisp = d; }

	bool setup(uint16_t runner_port, uint16_t master_port, const
			std::string &appname, unsigned int timeout = 2);
	void runWorker(AbstractWorkerActor *worker, ManagerActor *mgr);
	void shutdown();
	void runnerConnected(cml::TCPSocket *runnersock);
	void workerFinished(uint32_t wseq, const AbstractWorkerActor &worker);

private:
	Master();
	~Master();
	Master(const Master &UNUSED(o)): SINGLETON_MEMBER_INITLST,
			_state(NOT_READY), _msock(), _defdisp(), _activedisp(NULL),
			_data(NULL) {}
	Master& operator=(const Master &UNUSED(o)) { return *this; }
	State _state;
	cml::TCPSocket _msock;
	SimpleWorkerDispatcher _defdisp;
	IWorkerDispatcher *_activedisp;
	PData *_data;
};

}

#endif /* MASTER_H_ */
