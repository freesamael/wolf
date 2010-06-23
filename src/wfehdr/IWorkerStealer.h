/**
 * \file IWorkerStealer.h
 * \date Jun 23, 2010
 * \author samael
 */

#ifndef IWORKERSTEALER_H_
#define IWORKERSTEALER_H_

#include "TCPSocket.h"

namespace wfe
{

class Runner;

/**
 * \interface IWorkerStealer
 * IWorkerStealer defines the interface of classes to decide the stealing
 * policy.
 */
class IWorkerStealer
{
public:
	virtual ~IWorkerStealer() {}
	virtual void setRunner(Runner *runner) = 0;
	virtual void workerMissed() = 0;
	virtual void stealFailed(cml::TCPSocket *sender) = 0;
	virtual void workerArrived(cml::TCPSocket *sender) = 0;
};

}

#endif /* IWORKERSTEALER_H_ */
