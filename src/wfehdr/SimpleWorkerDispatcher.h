/**
 * \file SimpleWorkerDispatcher.h
 * \date Jun 9, 2010
 * \author samael
 */

#ifndef SIMPLEWORKERDISPATCHER_H_
#define SIMPLEWORKERDISPATCHER_H_

#include "IWorkerDispatcher.h"

namespace wfe
{

class SimpleWorkerDispatcher: public IWorkerDispatcher
{
public:
	cml::TCPSocket* choose(const std::vector<cml::TCPSocket *> &rsocks);

private:
	static unsigned _p;
};

}

#endif /* SIMPLEWORKERDISPATCHER_H_ */
