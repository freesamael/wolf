/**
 * \file CMaster.h
 * \date Apr 1, 2010
 * \author samael
 */

#ifndef CMASTER_H_
#define CMASTER_H_

#include <utility>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <netinet/in.h>
#include "CTime.h"
#include "CTcpServer.h"
#include "HelperMacros.h"
#include "AWorkerActor.h"
#include "CSimpleWorkerDispatcher.h"

namespace wolf
{

struct PData;

/**
 * Master plays the middle man between runners and workflow executors.
 */
class CMaster
{
	SINGLETON(CMaster);
public:
	typedef enum State {
		NOT_READY,
		READY,
		END
	} State;
	static const std::string StateString[];

	inline State state() const { return _state; }
	inline IWorkerDispatcher* dispatcher() const { return _activedisp; }
	inline void setDispatcher(IWorkerDispatcher *d) { _activedisp = d; }

	void init(int argc, char *argv[]);
	bool setup(in_port_t master_port, in_port_t runner_port, const
			std::string &appname = "default", unsigned int timeout = 2);
	void runWorker(AWorkerActor *worker, IManagerActor *mgr);
	void shutdown();
	void runnerConnected(CTcpSocket *runnersock);
	void putFinishWorker(uint32_t wseq, AWorkerActor *worker);
	void processFinishedWorker();
	unsigned numberOfRunners();
	CTime executionTime() const;

private:
	CMaster();
	~CMaster();
	CMaster(const CMaster &UNUSED(o)): SINGLETON_MEMBER_INITLST,
			_state(NOT_READY), _mserver(), _defdisp(), _activedisp(NULL),
			_d(NULL) {}
	CMaster& operator=(const CMaster &UNUSED(o)) { return *this; }
	State _state;						// Master state.
	CTcpServer _mserver;			// Master tcp server.
	CSimpleWorkerDispatcher _defdisp;	// Default worker dispatcher.
	IWorkerDispatcher *_activedisp;		// Active worker dispatcher.
	PData *_d;
};

}

#endif /* CMASTER_H_ */
