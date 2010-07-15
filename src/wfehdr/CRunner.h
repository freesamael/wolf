/**
 * \file CRunner.h
 * \date Apr 1, 2010
 * \author samael
 */

#ifndef CRUNNER_H_
#define CRUNNER_H_

#include <string>
#include <utility>
#include <inttypes.h>
#include "CTcpServer.h"
#include "CMutex.h"
#include "CWaitCondition.h"
#include "AWorkerActor.h"
#include "IWorkerStealer.h"

namespace wfe
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
	std::vector<cml::CTcpSocket *> runnerSocks();
	void connectRunner(const cml::CHostAddress &addr);
	void runnerConnected(cml::CTcpSocket *runnersock);
	void startWorking();
	void putWorker(uint32_t wseq, AWorkerActor *worker,
			cml::CTcpSocket *sender);
	std::pair<uint32_t, AWorkerActor *> takeWorker();
	void workerStealFailed(cml::CTcpSocket *sender);
	void sendWorkerFinished(uint32_t wseq, AWorkerActor *worker);
	void sendWorker(cml::CTcpSocket *sock, uint16_t nworkers);
	void sendWorkerSteal(cml::CTcpSocket *sock, uint16_t nworkers);
	void shutdown();

private:
	CRunner(const CRunner &UNUSED(o)): _id(0), _state(NOT_READY), _statemx(),
	_statewcond(), _mport(0), _rport(0), _stealer(NULL), _appname(), _rserver(),
	_d(NULL) {}
	CRunner& operator=(const CRunner &UNUSED(o)) { return *this; }

private:
	int _id;							// Runner id.
	State _state;						// Runner state.
	cml::CMutex _statemx;				// Runner state mutex.
	cml::CWaitCondition _statewcond;	// Runner state cond variable.
	in_port_t _mport, _rport;			// Master/Runner ports.
	IWorkerStealer *_stealer;			// Stealer.
	std::string _appname;				// DSM appname.
	cml::CTcpServer _rserver;			// Runner tcp server.
	PData *_d;
};

}

#endif /* CRUNNER_H_ */
