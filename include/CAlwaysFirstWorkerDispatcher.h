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

class CAlwaysFirstWorkerDispatcher: public wolf::IWorkerDispatcher
{
public:
	wolf::CTcpSocket* choose(const std::vector<wolf::CTcpSocket *> &rsocks)
		{ return rsocks[0]; }
};

}

#endif /* CALWAYSFIRSTWORKERDISPATCHER_H_ */
