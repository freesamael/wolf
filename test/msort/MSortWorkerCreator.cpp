/**
 * \file MSortWorkerCreator.cpp
 * \date Jun 28, 2010
 * \author samael
 */
#include <iostream>
#include <sstream>
#include <cstring>
#include <arpa/inet.h>
#include <HelperMacros.h>
#include "MSortWorkerCreator.h"
#include "MSortWorker.h"

using namespace wolf;
using namespace wolf;

MSortWorkerCreator::MSortWorkerCreator()
{

}

ITlvObject* MSortWorkerCreator::create(const ITlvBlock &blk) const
{
	if ((blk.length() % sizeof(uint32_t)) != 0) {
		PERR("Corrupted block.");
		return NULL;
	}

	CFlowVector<uint32_t> d;
	uint32_t offset = 0;
	while (offset < blk.length()) {
		uint32_t u32;
		memcpy(&u32, blk.value() + offset, sizeof(uint32_t));
		d.push_back(ntohl(u32));
		offset += sizeof(uint32_t);
	}

	MSortWorker *w = new MSortWorker();
	w->setVector(d);
	return w;
}
