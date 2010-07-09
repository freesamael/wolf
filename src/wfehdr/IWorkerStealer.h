/**
 * \file IWorkerStealer.h
 * \date Jun 23, 2010
 * \author samael
 */

#ifndef IWORKERSTEALER_H_
#define IWORKERSTEALER_H_

#include "CTcpSocket.h"

namespace wfe
{

class CRunner;

/**
 * \interface IWorkerStealer
 * IWorkerStealer defines the interface of classes to decide the stealing
 * policy.
 */
class IWorkerStealer
{
public:
	virtual ~IWorkerStealer() {}
	/// Set the runner. Called on construction of Runner.
	virtual void setRunner(CRunner *runner) = 0;
	/// Called when a worker miss event happen.
	/// \note This function must be thread-safe.
	virtual void workerMissed() = 0;
	/// Called when a stealing failed.
	virtual void stealFailed(cml::CTcpSocket *sender) = 0;
	/// Called when a worker arrived (from either a runner or master).
	virtual void workerArrived(cml::CTcpSocket *sender) = 0;
};

}

#endif /* IWORKERSTEALER_H_ */
