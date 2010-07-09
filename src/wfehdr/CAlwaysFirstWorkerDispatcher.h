/**
 * \file CAlwaysFirstWorkerDispatcher.h
 * \date Jun 23, 2010
 * \author samael
 */

#ifndef CALWAYSFIRSTWORKERDISPATCHER_H_
#define CALWAYSFIRSTWORKERDISPATCHER_H_

#include "IWorkerDispatcher.h"

namespace wfe
{

class CAlwaysFirstWorkerDispatcher: public wfe::IWorkerDispatcher
{
public:
	cml::CTcpSocket* choose(const std::vector<cml::CTcpSocket *> &rsocks)
		{ return rsocks[0]; }
};

}

#endif /* CALWAYSFIRSTWORKERDISPATCHER_H_ */
