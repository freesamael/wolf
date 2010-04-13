/**
 * \file TLVObjectFactoryAutoRegistry.h
 * \date Apr 4, 2010
 * \author samael
 */

#ifndef TLVOBJECTFACTORYAUTOREGISTRY_H_
#define TLVOBJECTFACTORYAUTOREGISTRY_H_

#include <typeinfo>
#include <string>
#include "ITLVObjectCreator.h"

namespace cml
{

/**
 * Auto registry used to register type id and creator to TLVObjectFactory. In
 * most case you should use TLV_OBJECT_REGISTRATION(type, id, creator) helper
 * macro which generates a static TLVObjectFactoryAutoRegistry object rather
 * than directly construct a TLVObjectFactoryAutoRegister manually.
 */
class TLVObjectFactoryAutoRegistry
{
public:
	TLVObjectFactoryAutoRegistry(const std::string &type, unsigned short id,
			ITLVObjectCreator *creator);
};

}

#endif /* TLVOBJECTFACTORYAUTOREGISTOR_H_ */
