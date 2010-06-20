/**
 * \file HelloWorker.cpp
 * \date Apr 14, 2010
 * \author samael
 */

#include <TLVObjectFactoryAutoRegistry.h>
#include <HelperMacros.h>
#include "HelloWorker.h"
#include "HelloWorkerCreator.h"

#define TLV_TYPE_HELLO	100

using namespace cml;
using namespace wfe;

TLV_OBJECT_REGISTRATION(HelloWorker, TLV_TYPE_HELLO, HelloWorkerCreator);

StandardTLVBlock* HelloWorker::toTLVBlock() const
{
	return new StandardTLVBlock(TLV_TYPE_HELLO);
}
