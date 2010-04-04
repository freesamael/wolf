/*
 * TLVObjectFactoryAutoRegistor.h
 *
 *  Created on: Apr 4, 2010
 *      Author: samael
 */

#ifndef TLVOBJECTFACTORYAUTOREGISTOR_H_
#define TLVOBJECTFACTORYAUTOREGISTOR_H_

#include <typeinfo>
#include <string>
#include "ITLVObjectCreator.h"

namespace cml
{

class TLVObjectFactoryAutoRegistor
{
public:
	TLVObjectFactoryAutoRegistor(const std::string &type, unsigned short id,
			ITLVObjectCreator *creator);
};

}

#define TLV_OBJECT_REGISTRATION( type, id, creator ) \
	static cml::TLVObjectFactoryAutoRegistor CONCATE(autoreg, __LINE__)( \
			typeid(type).name(), id, new creator() )

#define CONCATE(x, y) __CONCATE(x, y)
#define __CONCATE(x, y) x##y

#endif /* TLVOBJECTFACTORYAUTOREGISTOR_H_ */
