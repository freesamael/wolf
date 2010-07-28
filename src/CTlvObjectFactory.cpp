/**
 * \file CTlvObjectFactory.cpp
 * \date Mar 10, 2010
 * \author samael
 */

#include <typeinfo>
#include "CTlvObjectFactory.h"
#include "ITlvObjectCreator.h"
#include "CTlvBlock.h"
#include "CTlvStringCreator.h"
#include "CTlvUint16Creator.h"
#include "CTlvUint32Creator.h"
#include "CSingletonAutoDestructor.h"
#include "CmlTLVTypes.h"

using namespace std;

namespace wolf
{

SINGLETON_REGISTRATION(CTlvObjectFactory);
SINGLETON_REGISTRATION_END();

CTlvObjectFactory::~CTlvObjectFactory()
{
	map<string, ITlvObjectCreator *>::iterator iter;
	for (iter = _creators.begin(); iter != _creators.end(); ++iter)
		delete iter->second;
}

/**
 * Register a host type corresponding a TLV type id. If the id has already bound
 * with a type, it overwrites the original type registered before.
 *
 * \param id
 * ID used in TLV type.
 *
 * \param name
 * Type name, i.e. TYPENAME(Class).
 */
void CTlvObjectFactory::registerType(uint16_t id, const std::string &name)
{
	map<uint16_t, string>::iterator iter;

	// Erase registered one if any.
	if ((iter = _typenames.find(id)) != _typenames.end())
		_typenames.erase(iter);

	// Register type.
	_typenames[id] = name;
}

/**
 * Register a creator to the factory.
 *
 * \param name
 * Type name, i.e. TYPENAME(Class).
 *
 * \param creator
 * Associated creator.
 *
 * \note
 * Factory keeps the ownership which means it deletes creators on destruction.
 */
void CTlvObjectFactory::registerCreator(const std::string &name,
		ITlvObjectCreator *creator)
{
	if (creator) {
		map<string, ITlvObjectCreator *>::iterator iter;
		if ((iter = _creators.find(name)) != _creators.end()) {
			delete iter->second;
			_creators.erase(iter);
		}
		_creators[name] = creator;
	}
}

/**
 * Get host typename by giving TLV type id.
 *
 * \return
 * Typename.
 */
string CTlvObjectFactory::lookupTypeName(uint16_t id) 
{
	map<uint16_t, string>::iterator iter;
	for (iter = _typenames.begin(); iter != _typenames.end(); ++iter) {
		if (iter->first == id)
			return iter->second;
	}
	throw XTlvObject(XTlvObject::INVALID_TYPE_ID, id);
}

/**
 * Create a object by typename.
 *
 * \return
 * Object created.
 */
ITlvObject* CTlvObjectFactory::createTLVObject(const string &type_name)
		
{
	map<string, ITlvObjectCreator *>::iterator iter;
	if ((iter = _creators.find(type_name)) != _creators.end())
		return iter->second->create();
	throw XTlvObject(XTlvObject::NO_SUITABLE_CREATOR, TLV_TYPE_INVALID, type_name);
}

/**
 * Overloaded creation function.
 */
ITlvObject* CTlvObjectFactory::createTLVObject(uint16_t type_id)
		
{
	return createTLVObject(lookupTypeName(type_id));
}

/**
 * Create a object from corresponding TLV block.
 *
 * \return
 * Object created.
 */
ITlvObject* CTlvObjectFactory::createTLVObject(const ITlvBlock &blk)
		
{
	map<string, ITlvObjectCreator *>::iterator iter;
	if ((iter = _creators.find(lookupTypeName(blk.type()))) !=
			_creators.end()) {
		return iter->second->create(blk);
	}
	throw XTlvObject(XTlvObject::NO_SUITABLE_CREATOR, blk.type(),
			lookupTypeName(blk.type()));
}

}
