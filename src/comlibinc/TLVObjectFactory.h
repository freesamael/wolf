/**
 * \file TLVObjectFactory.h
 * \date Mar 10, 2010
 * \author samael
 */

#ifndef TLVOBJECTFACTORY_H_
#define TLVOBJECTFACTORY_H_

#include <map>
#include <string>
#include "ITLVObject.h"
#include "ITLVObjectCreator.h"
#include "ITLVBlock.h"

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
public:
	static TLVObjectFactory* instance();
	static void release();
	void registerType(const std::string &name, unsigned short id);
	void registerCreator(const std::string &name, ITLVObjectCreator *creator);
	unsigned short lookupTypeId(const std::string &name);
	std::string lookupTypeName(unsigned short id);
	ITLVObject* createTLVObject(const std::string &type_name);
	ITLVObject* createTLVObject(unsigned short type_id);
	ITLVObject* createTLVObject(const ITLVBlock &blk);

private:
	TLVObjectFactory();
	~TLVObjectFactory();
	static TLVObjectFactory *_instance;
	std::map<std::string, unsigned short> _typeids;
	std::map<std::string, ITLVObjectCreator *> _creators;
};

}

#endif /* TLVOBJECTFACTORY_H_ */
