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
		uint16_t id,ITLVObjectCreator *creator)
{
	TLVObjectFactory::instance()->registerType(id, type);
	TLVObjectFactory::instance()->registerCreator(type, creator);
}

}
