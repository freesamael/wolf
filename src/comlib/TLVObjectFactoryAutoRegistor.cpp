/*
 * TLVObjectFactoryAutoRegistor.cpp
 *
 *  Created on: Apr 4, 2010
 *      Author: samael
 */

#include <iostream>
#include "TLVObjectFactoryAutoRegistor.h"
#include "TLVObjectFactory.h"

using namespace std;

namespace cml
{

TLVObjectFactoryAutoRegistor::TLVObjectFactoryAutoRegistor(const std::string &type,
		unsigned short id,ITLVObjectCreator *creator)
{
	TLVObjectFactory::instance()->registerType(type, id);
	TLVObjectFactory::instance()->registerCreator(type, creator);

	cout << "Registered " << type << " with id " << id << endl;
}

}
