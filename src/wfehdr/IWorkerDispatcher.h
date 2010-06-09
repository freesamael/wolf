/**
 * \file IWorkerDispatcher.h
 * \date Jun 9, 2010
 * \author samael
 */

#ifndef IWORKERDISPATCHER_H_
#define IWORKERDISPATCHER_H_

#include <vector>
#include "TCPSocket.h"

namespace wfe
{

/**
 * \interface IWorkerDispatcher
 */
class IWorkerDispatcher
{
public:
	virtual ~IWorkerDispatcher() {}
	/// Choose a runner from all runners to dispatch worker.
	virtual cml::TCPSocket* choose(const std::vector<cml::TCPSocket *> &rsocks) = 0;
};

}

#endif /* IWORKERDISPATCHER_H_ */
