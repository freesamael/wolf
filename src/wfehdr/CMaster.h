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
#include "CTime.h"
#include "CTcpSocket.h"
#include "HelperMacros.h"
#include "AWorkerActor.h"
#include "CSimpleWorkerDispatcher.h"

namespace wfe
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
	bool setup(uint16_t master_port, uint16_t runner_port, const
			std::string &appname = "default", unsigned int timeout = 2);
	void runWorker(AWorkerActor *worker, IManagerActor *mgr);
	void shutdown();
	void runnerConnected(cml::CTcpSocket *runnersock);
	void putFinishWorker(uint32_t wseq, AWorkerActor *worker);
	void processFinishedWorker();
	unsigned numberOfRunners();
	cml::CTime executionTime() const;

private:
	CMaster();
	~CMaster();
	CMaster(const CMaster &UNUSED(o)): SINGLETON_MEMBER_INITLST,
			_state(NOT_READY), _msock(), _defdisp(), _activedisp(NULL),
			_d(NULL) {}
	CMaster& operator=(const CMaster &UNUSED(o)) { return *this; }
	State _state;
	cml::CTcpSocket _msock;
	CSimpleWorkerDispatcher _defdisp;
	IWorkerDispatcher *_activedisp;
	PData *_d;
};

}

#endif /* CMASTER_H_ */
