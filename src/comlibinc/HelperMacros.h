/**
 * \file HelperMacros.h
 * Defines helper macros.
 */

#ifndef HELPERMACROS_H_
#define HELPERMACROS_H_

/**
 * \def CONCATE(x, y)
 * Concatenates two symbols even they are other macros.
 */
#define CONCATE(x, y) __CONCATE(x, y)
#define __CONCATE(x, y) x##y

/**
 * \def TLV_OBJECT_REGISTRATION(type, id, creator)
 * Registers a TLV object to TLVObjectFactory with given id and creator.
 */
#define TLV_OBJECT_REGISTRATION( type, id, creator ) \
	static cml::TLVObjectFactoryAutoRegistry CONCATE(autoreg, __LINE__)( \
			typeid(type).name(), id, new creator() )

/**
 * \def SINGLETON_REGISTRATION(type)
 * Defines a singleton object. The object must have release() method.
 */
#define SINGLETON_REGISTRATION( type ) \
	static cml::SingletonAutoDestructor< type > CONCATE(autodes, __LINE__)

#endif /* HELPERMACROS_H_ */
