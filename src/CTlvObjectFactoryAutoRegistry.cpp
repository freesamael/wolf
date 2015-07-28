/**
 * \file CTlvObjectFactoryAutoRegistry.cpp
 * \date Apr 4, 2010
 * \author samael
 */

#include "CTlvObjectFactoryAutoRegistry.h"
#include "CTlvObjectFactory.h"

namespace wolf
{

CTlvObjectFactoryAutoRegistry::CTlvObjectFactoryAutoRegistry(const std::string &type,
		uint32_t id,ITlvObjectCreator *creator)
{
	CTlvObjectFactory::instance()->registerType(id, type);
	CTlvObjectFactory::instance()->registerCreator(type, creator);
}

}
