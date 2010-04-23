/**
 * \file HelperMacros.h
 * This file defines helper macros for wolf.
 */

#ifndef HELPERMACROS_H_
#define HELPERMACROS_H_

/**
 * \def TYPENAME(type)
 * Get the name of type in string.
 *
 * \note
 * \#include \<typeinfo\>
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
 *
 * \note
 * \#include \<typeinfo\> <br>
 * \#include \<TLVObjectFactoryAutoRegistry.h\>
 */
#define TLV_OBJECT_REGISTRATION(type, id, creator) \
	static cml::TLVObjectFactoryAutoRegistry CONCATE(autoreg, __LINE__)(\
			typeid(type).name(), id, new creator())

/**
 * \def SINGLETON(type)
 * Declare a singleton type.
 *
 * \note
 * \#include \<vector\> <br>
 * \#include \<iostream\>
 */
#define SINGLETON(type) \
	public: \
		static type* instance(); \
		static void release() { SINGLETON_RELEASE_BODY(); } \
		inline void registerDep(void (*rls)()) { _deps.push_back(rls); } \
	private: \
		void releaseDeps() { SINGLETON_RELEASE_DEPS_BODY(); } \
		static type* _instance; \
		std::vector<void (*)()> _deps

/**
 * \def SINGLETON_RELEASE_BODY()
 * The body of release() function.
 */
#define SINGLETON_RELEASE_BODY() \
	if (_instance) { \
		PINFO("Releasing"); \
		_instance->releaseDeps(); \
		delete _instance; \
		_instance = NULL; \
	} \
	return

/**
 * \def SINGLETON_RELEASE_DEPS_BODY()
 * The body of releaseDeps() function.
 */
#define SINGLETON_RELEASE_DEPS_BODY() \
	for (unsigned i = 0; i < _deps.size(); i++) \
		(*_deps[i])()

/**
 * \def SINGLETON_REGISTRATION(type)
 * Register a singleton object.
 *
 * \note
 * \#include \<SingletonAutoDestructor.h\>
 */
#define SINGLETON_REGISTRATION(type) \
	static cml::SingletonAutoDestructor< type > CONCATE(autodes, __LINE__); \
	type* type::_instance = NULL; \
	type* type::instance() { \
		if (!_instance) { \
			_instance = new type()

/**
 * \def SINGLETON_DEPENDS(self_type, dep_type)
 * Declare that self_type depends on dep_type. It affects the destruction
 * sequence.
 */
#define SINGLETON_DEPENDS(self_type, dep_type) \
			dep_type::instance()->registerDep(&self_type::release)

/**
 * \def SINGLETON_REGISTRATION_END()
 * The end clause of singleton registration.
 */
#define SINGLETON_REGISTRATION_END() \
		} \
		return _instance; \
	}

/**
 * \def PERR(str)
 * Print an error message. str is a stream in "a << b << c" format.
 *
 * \note
 * \#include \<iostream\>
 */
#define PERR(str) \
	std::cerr << "Error: " << __PRETTY_FUNCTION__ << ": " << __LINE__ << ": " \
	<< str << std::endl

#ifdef DEBUG
/**
 * \def PINFO(str)
 * Print an info message. str is a stream in "a << b << c" format.
 *
 * \note
 * \#include \<iostream\>
 */
#define PINFO(str) \
	std::cout << "Info: " << __PRETTY_FUNCTION__ << ": " << __LINE__ << ": " \
	<< str << std::endl
#else
#define PINFO(str)
#endif /* DEBUG */

#endif /* HELPERMACROS_H_ */
