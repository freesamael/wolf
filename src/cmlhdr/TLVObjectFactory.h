/**
 * \file TLVObjectFactory.h
 * \date Mar 10, 2010
 * \author samael
 */

#ifndef TLVOBJECTFACTORY_H_
#define TLVOBJECTFACTORY_H_

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "ITLVObject.h"
#include "ITLVObjectCreator.h"
#include "ITLVBlock.h"
#include "HelperMacros.h"

namespace cml
{

/**
 * The central factory for TLV objects. TLVReaderWriter uses TLVObjectFactory
 * to create a TLV object from a incoming message of TLV blocks. All TLV object
 * should register its type and creator to TLVObjectFactory in order to make the
 * creation process work.
 */
class TLVObjectFactory
{
	SINGLETON(TLVObjectFactory);
public:
	void registerType(uint16_t id, const std::string &name);
	void registerCreator(const std::string &name, ITLVObjectCreator *creator);
	std::string lookupTypeName(uint16_t id);
	ITLVObject* createTLVObject(const std::string &type_name);
	ITLVObject* createTLVObject(uint16_t type_id);
	ITLVObject* createTLVObject(const ITLVBlock &blk);

private:
	TLVObjectFactory(): SINGLETON_MEMBER_INITLST, _typenames(), _creators() {}
	~TLVObjectFactory();
	std::map<uint16_t, std::string> _typenames;
	std::map<std::string, ITLVObjectCreator *> _creators;
};

}

#endif /* TLVOBJECTFACTORY_H_ */
