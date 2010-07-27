/**
 * \file TlvObjectFactoryAutoRegistry.cpp
 * \date Apr 4, 2010
 * \author samael
 */

#include "CTlvObjectFactoryAutoRegistry.h"
#include "CTlvObjectFactory.h"

namespace wolf
{

CTlvObjectFactoryAutoRegistry::CTlvObjectFactoryAutoRegistry(const std::string &type,
		uint16_t id,ITlvObjectCreator *creator)
{
	CTlvObjectFactory::instance()->registerType(id, type);
	CTlvObjectFactory::instance()->registerCreator(type, creator);
}

}
