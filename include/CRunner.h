/**
 * \file CRunner.h
 * \date Apr 1, 2010
 * \author samael
 */

#ifndef CRUNNER_H_
#define CRUNNER_H_

#include <string>
#include <utility>
#include <unistd.h>
#include <netinet/in.h>
#include "CTcpServer.h"
#include "CMutex.h"
#include "CWaitCondition.h"
#include "AWorkerActor.h"
#include "IWorkerStealer.h"

namespace wolf
{

struct PData;

/**
 * The runner which is responsible for worker executions.
 */
class CRunner
{
public:
	typedef enum State {
		NOT_READY,
		READY,
		WORKING,
		END
	} State;

	CRunner(in_port_t master_port, in_port_t runner_port, IWorkerStealer *ws,
			const std::string &appname = "default");
	~CRunner();
	void run();

	int id() const { return _id; }
	std::vector<CTcpSocket *> runnerSocks();
	void connectRunner(const CHostAddress &addr);
	void runnerConnected(CTcpSocket *runnersock);
	void startWorking();
	void putWorker(uint32_t wseq, AWorkerActor *worker,
			CTcpSocket *sender);
	std::pair<uint32_t, AWorkerActor *> takeWorker();
	void workerStealFailed(CTcpSocket *sender);
	void sendWorkerFinished(uint32_t wseq, AWorkerActor *worker);
	void sendWorker(CTcpSocket *sock, uint32_t nworkers);
	void sendWorkerSteal(CTcpSocket *sock, uint32_t nworkers);
	void shutdown();

private:
	CRunner(const CRunner &UNUSED(o)): _id(0), _state(NOT_READY), _statemx(),
	_statewcond(), _mport(0), _rport(0), _stealer(NULL), _appname(), _rserver(),
	_d(NULL) {}
	CRunner& operator=(const CRunner &UNUSED(o)) { return *this; }

private:
	int _id;							// Runner id.
	State _state;						// Runner state.
	CMutex _statemx;				// Runner state mutex.
	CWaitCondition _statewcond;	// Runner state cond variable.
	in_port_t _mport, _rport;			// Master/Runner ports.
	IWorkerStealer *_stealer;			// Stealer.
	std::string _appname;				// DSM appname.
	CTcpServer _rserver;			// Runner tcp server.
	PData *_d;
};

}

#endif /* CRUNNER_H_ */
