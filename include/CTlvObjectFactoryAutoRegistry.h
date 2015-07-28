/**
 * \file CTlvObjectFactoryAutoRegistry.h
 * \date Apr 4, 2010
 * \author samael
 */

#ifndef CTLVOBJECTFACTORYAUTOREGISTRY_H_
#define CTLVOBJECTFACTORYAUTOREGISTRY_H_

#include <typeinfo>
#include <string>
#include "ITlvObjectCreator.h"

namespace wolf
{

/**
 * Auto registry used to register type id and creator to TLVObjectFactory. In
 * most case you should use TLV_OBJECT_REGISTRATION(type, id, creator) helper
 * macro which generates a static TLVObjectFactoryAutoRegistry object rather
 * than directly construct a TLVObjectFactoryAutoRegister manually.
 */
class CTlvObjectFactoryAutoRegistry
{
public:
	CTlvObjectFactoryAutoRegistry(const std::string &type, uint32_t id,
			ITlvObjectCreator *creator);
};

}

#endif /* CTLVOBJECTFACTORYAUTOREGISTOR_H_ */
