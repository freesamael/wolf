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

class CSimpleWorkerDispatcher: public IWorkerDispatcher
{
public:
	wolf::CTcpSocket* choose(const std::vector<wolf::CTcpSocket *> &rsocks);

private:
	static unsigned _p;
};

}

#endif /* CSIMPLEWORKERDISPATCHER_H_ */
