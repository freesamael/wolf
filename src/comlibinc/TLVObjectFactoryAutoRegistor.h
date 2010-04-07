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

/**
 * Auto register used to register type id and creator to TLVObjectFactory.
 */
class TLVObjectFactoryAutoRegistor
{
public:
	TLVObjectFactoryAutoRegistor(const std::string &type, unsigned short id,
			ITLVObjectCreator *creator);
};

}

#endif /* TLVOBJECTFACTORYAUTOREGISTOR_H_ */
