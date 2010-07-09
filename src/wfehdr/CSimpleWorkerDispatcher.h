/**
 * \file CSimpleWorkerDispatcher.h
 * \date Jun 9, 2010
 * \author samael
 */

#ifndef CSIMPLEWORKERDISPATCHER_H_
#define CSIMPLEWORKERDISPATCHER_H_

#include "IWorkerDispatcher.h"

namespace wfe
{

class CSimpleWorkerDispatcher: public IWorkerDispatcher
{
public:
	cml::CTcpSocket* choose(const std::vector<cml::CTcpSocket *> &rsocks);

private:
	static unsigned _p;
};

}

#endif /* CSIMPLEWORKERDISPATCHER_H_ */
