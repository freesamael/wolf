/*
 * TLVObjectFactoryAutoRegistor.cpp
 *
 *  Created on: Apr 4, 2010
 *      Author: samael
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
