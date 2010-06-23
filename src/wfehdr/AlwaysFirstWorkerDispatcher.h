/**
 * \file AlwaysFirstWorkerDispatcher.h
 * \date Jun 23, 2010
 * \author samael
 */

#ifndef ALWAYSFIRSTWORKERDISPATCHER_H_
#define ALWAYSFIRSTWORKERDISPATCHER_H_

#include "IWorkerDispatcher.h"

namespace wfe
{

class AlwaysFirstWorkerDispatcher: public wfe::IWorkerDispatcher
{
public:
	cml::TCPSocket* choose(const std::vector<cml::TCPSocket *> &rsocks)
		{ return rsocks[0]; }
};

}

#endif /* ALWAYSFIRSTWORKERDISPATCHER_H_ */
