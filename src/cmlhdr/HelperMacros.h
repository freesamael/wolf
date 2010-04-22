/**
 * \file HelperMacros.h
 * This file defines helper macros for wolf.
 */

#ifndef HELPERMACROS_H_
#define HELPERMACROS_H_

#include <cstdio>
#include <iostream>
#include <typeinfo>

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

/// Print an error message.
#define PERR(str) \
	std::cerr << "Error: " << __PRETTY_FUNCTION__ << ": " << __LINE__ << ": " \
	<< str << std::endl

#ifdef DEBUG
/// Print an info message.
#define PINFO(str) \
	std::cout << "Info: " << __PRETTY_FUNCTION__ << ": " << __LINE__ << ": " \
	<< str << std::endl
#else
#define PINFO(str)
#endif /* DEBUG */

#endif /* HELPERMACROS_H_ */
