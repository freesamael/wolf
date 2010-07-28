/**
 * \file CSimpleWorkerDispatcher.h
 * \date Jun 9, 2010
 * \author samael
 */

#ifndef CSIMPLEWORKERDISPATCHER_H_
#define CSIMPLEWORKERDISPATCHER_H_

#include "IWorkerDispatcher.h"

namespace wolf
{

/**
 * A dispatching policy that dispatches workers to all runners one-by-one.
 *
 * \see IWorkerDispatcher
 */
class CSimpleWorkerDispatcher: public IWorkerDispatcher
{
public:
	CTcpSocket* choose(const std::vector<CTcpSocket *> &rsocks);

private:
	static unsigned _p;
};

}

#endif /* CSIMPLEWORKERDISPATCHER_H_ */
