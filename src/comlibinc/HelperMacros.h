/**
 * \file HelperMacros.h
 * This file defines helper macros for wolf.
 */

#ifndef HELPERMACROS_H_
#define HELPERMACROS_H_

/**
 * \def TYPENAME(type)
 * Get the name of type in string.
 */
#define TYPENAME(type) (typeid(type).name())

/**
 * \def CONCATE(x, y)
 * Concatenate two symbols even they are other macros.
 */
#define CONCATE(x, y) __CONCATE(x, y)
#define __CONCATE(x, y) x##y

/**
 * \def TLV_OBJECT_REGISTRATION(type, id, creator)
 * Register a TLV object to TLVObjectFactory with given id and creator.
 */
#define TLV_OBJECT_REGISTRATION( type, id, creator ) \
	static cml::TLVObjectFactoryAutoRegistry CONCATE(autoreg, __LINE__)( \
			typeid(type).name(), id, new creator() )

/**
 * \def SINGLETON_REGISTRATION(type)
 * Define a singleton object. The object must have release() method.
 */
#define SINGLETON_REGISTRATION( type ) \
	static cml::SingletonAutoDestructor< type > CONCATE(autodes, __LINE__)

#endif /* HELPERMACROS_H_ */
