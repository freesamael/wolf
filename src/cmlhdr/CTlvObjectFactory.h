/**
 * \file CTlvObjectFactory.h
 * \date Mar 10, 2010
 * \author samael
 */

#ifndef CTLVOBJECTFACTORY_H_
#define CTLVOBJECTFACTORY_H_

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "ITlvObject.h"
#include "ITlvObjectCreator.h"
#include "ITlvBlock.h"
#include "HelperMacros.h"

namespace cml
{

/**
 * The central factory for TLV objects. TLVReaderWriter uses TLVObjectFactory
 * to create a TLV object from a incoming message of TLV blocks. All TLV object
 * should register its type and creator to TLVObjectFactory in order to make the
 * creation process work.
 */
class CTlvObjectFactory
{
	SINGLETON(CTlvObjectFactory);
public:
	void registerType(uint16_t id, const std::string &name);
	void registerCreator(const std::string &name, ITlvObjectCreator *creator);
	std::string lookupTypeName(uint16_t id);
	ITlvObject* createTLVObject(const std::string &type_name);
	ITlvObject* createTLVObject(uint16_t type_id);
	ITlvObject* createTLVObject(const ITlvBlock &blk);

private:
	CTlvObjectFactory(): SINGLETON_MEMBER_INITLST, _typenames(), _creators() {}
	~CTlvObjectFactory();
	std::map<uint16_t, std::string> _typenames;
	std::map<std::string, ITlvObjectCreator *> _creators;
};

}

#endif /* CTLVOBJECTFACTORY_H_ */
