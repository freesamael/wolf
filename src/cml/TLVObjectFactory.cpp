/**
 * \file TLVObjectFactory.cpp
 * \date Mar 10, 2010
 * \author samael
 */

#include <typeinfo>
#include "TLVObjectFactory.h"
#include "ITLVObjectCreator.h"
#include "TLVBlock.h"
#include "TLVStringCreator.h"
#include "TLVUInt16Creator.h"
#include "TLVUInt32Creator.h"
#include "SingletonAutoDestructor.h"

using namespace std;

namespace cml
{

SINGLETON_REGISTRATION(TLVObjectFactory);
SINGLETON_REGISTRATION_END();

TLVObjectFactory::~TLVObjectFactory()
{
	map<string, ITLVObjectCreator *>::iterator iter;
	for (iter = _creators.begin(); iter != _creators.end(); iter++)
		delete iter->second;
}

/**
 * Register a net type corresponding to a host type. If the net type is already
 * registered, it overwrites the registered type.
 *
 * \param name
 * Type name, i.e. typeid(Class).name().
 *
 * \param id
 * ID used in TLV type.
 */
void TLVObjectFactory::registerType(const std::string &name, uint16_t id)
{
	map<string, uint16_t>::iterator iter;

	// Erase registered one if any.
	if ((iter = _typeids.find(name)) != _typeids.end())
		_typeids.erase(iter);

	// Register type.
	_typeids[name] = id;
}

/**
 * Register a creator to the factory.
 *
 * \param name
 * Type name, i.e. typeid(Class).name().
 *
 * \param creator
 * Associated creator.
 *
 * \note
 * Factory keeps the ownership which means it deletes creators on destruction.
 */
void TLVObjectFactory::registerCreator(const std::string &name,
		ITLVObjectCreator *creator)
{
	if (creator) {
		map<string, ITLVObjectCreator *>::iterator iter;
		if ((iter = _creators.find(name)) != _creators.end()) {
			delete iter->second;
			_creators.erase(iter);
		}
		_creators[name] = creator;
	}
}

/**
 * Get TLV type id by giving host typename (typeid().name()).
 *
 * \return
 * Type id or TLV_TYPE_INVALID if nothing found.
 */
uint16_t TLVObjectFactory::lookupTypeId(const string &name)
{
	map<string, uint16_t>::iterator iter;
	if ((iter = _typeids.find(name)) != _typeids.end())
		return iter->second;
	return TLV_TYPE_INVALID;
}

/**
 * Get host typename (typeid().name()) by giving TLV type id.
 *
 * \return
 * Typename or empty string if nothing found.
 */
string TLVObjectFactory::lookupTypeName(uint16_t id)
{
	map<string, uint16_t>::iterator iter;
	for (iter = _typeids.begin(); iter != _typeids.end(); iter++) {
		if (iter->second == id)
			return iter->first;
	}
	return string();
}

/**
 * Create a object by typename (typeid().name()).
 *
 * \return
 * Object created, or NULL if no corresponding creators found.
 */
ITLVObject* TLVObjectFactory::createTLVObject(const string &type_name)
{
	PINFO("Creating an object.");
	map<string, ITLVObjectCreator *>::iterator iter;
	if ((iter = _creators.find(type_name)) != _creators.end())
		return iter->second->create();
	return NULL;
}

/**
 * Overloaded creation function.
 */
ITLVObject* TLVObjectFactory::createTLVObject(uint16_t type_id)
{
	PINFO("Creating an object.");
	return createTLVObject(lookupTypeName(type_id));
}

/**
 * Create a object from corresponding TLV block.
 *
 * \return
 * Object created, or NULL if no proper creators found.
 */
ITLVObject* TLVObjectFactory::createTLVObject(const ITLVBlock &blk)
{
	PINFO("Creating an object, type id = " << blk.type() << ".");
	map<string, ITLVObjectCreator *>::iterator iter;
	if ((iter = _creators.find(lookupTypeName(blk.type()))) !=
			_creators.end()) {
		return iter->second->create(blk);
	}
	PERR("No suitable creator found for type" << blk.type());
	return NULL;
}

}
