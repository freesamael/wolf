/**
 * \file CAlwaysFirstWorkerDispatcher.h
 * \date Jun 23, 2010
 * \author samael
 */

#ifndef CALWAYSFIRSTWORKERDISPATCHER_H_
#define CALWAYSFIRSTWORKERDISPATCHER_H_

#include "IWorkerDispatcher.h"

namespace wolf
{

/**
 * A dispatching policy that always dispatches to first runner.
 *
 * \see IWorkerDispatcher
 */
class CAlwaysFirstWorkerDispatcher: public IWorkerDispatcher
{
public:
	CTcpSocket* choose(const std::vector<CTcpSocket *> &rsocks)
		{ return rsocks[0]; }
};

}

#endif /* CALWAYSFIRSTWORKERDISPATCHER_H_ */
