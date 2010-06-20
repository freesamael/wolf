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
 * Register a host type corresponding a TLV type id. If the id has already bound
 * with a type, it overwrites the original type registered before.
 *
 * \param id
 * ID used in TLV type.
 *
 * \param name
 * Type name, i.e. typeid(Class).name().
 */
void TLVObjectFactory::registerType(uint16_t id, const std::string &name)
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
 * Get host typename (typeid().name()) by giving TLV type id.
 *
 * \return
 * Typename or empty string if nothing found.
 */
string TLVObjectFactory::lookupTypeName(uint16_t id)
{
	map<uint16_t, string>::iterator iter;
	for (iter = _typenames.begin(); iter != _typenames.end(); iter++) {
		if (iter->first == id)
			return iter->second;
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
	PINF_3("Creating an object.");
	map<string, ITLVObjectCreator *>::iterator iter;
	if ((iter = _creators.find(type_name)) != _creators.end())
		return iter->second->create();
	PERR("No suite creator found.");
	return NULL;
}

/**
 * Overloaded creation function.
 */
ITLVObject* TLVObjectFactory::createTLVObject(uint16_t type_id)
{
	PINF_3("Creating an object.");
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
	PINF_3("Creating an object, type id = " << blk.type() << ".");
	map<string, ITLVObjectCreator *>::iterator iter;
	if ((iter = _creators.find(lookupTypeName(blk.type()))) !=
			_creators.end()) {
		return iter->second->create(blk);
	}
	PERR("No suitable creator found for type " << blk.type());
	return NULL;
}

}
