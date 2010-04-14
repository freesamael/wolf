/**
 * \file TLVObjectFactoryAutoRegistry.cpp
 * \date Apr 4, 2010
 * \author samael
 */

#include "TLVObjectFactoryAutoRegistry.h"
#include "TLVObjectFactory.h"

namespace cml
{

TLVObjectFactoryAutoRegistry::TLVObjectFactoryAutoRegistry(const std::string &type,
		unsigned short id,ITLVObjectCreator *creator)
{
	TLVObjectFactory::instance()->registerType(type, id);
	TLVObjectFactory::instance()->registerCreator(type, creator);
}

}