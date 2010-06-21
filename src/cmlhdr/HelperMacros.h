/**
 * \file HelperMacros.h
 * This file defines helper macros for wolf.
 */

#ifndef HELPERMACROS_H_
#define HELPERMACROS_H_

#include <pthread.h>

extern pthread_mutex_t g_mxcout;
extern pthread_mutex_t g_mxcerr;

#ifndef UNUSED
#ifdef __GNUC__
#define UNUSED(x) x __attribute__((unused))
#else
#define UNUSED(x) x
#endif /* __GNUC__ */
#endif /* UNUSED */

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
	static cml::TLVObjectFactoryAutoRegistry CONCATE(__autoreg, __LINE__)( \
			typeid(type).name(), id, new creator())

/**
 * \def SINGLETON(type)
 * Declare a singleton type. The class should have a private default constructor
 * and should put SINGLETON_MEM_INITLST within the member initialization list.
 *
 * \note
 * \#include \<vector\> <br>
 * \#include \<iostream\> <br>
 * \#include \<sstream\>
 */
#define SINGLETON(type)                                                        \
	public:                                                                    \
		static type* instance();                                               \
		static void release() { SINGLETON_RELEASE_BODY(); }                    \
		inline void registerDependant(void (*rls)()) { _deps.push_back(rls); } \
	private:                                                                   \
		void releaseDependants() { SINGLETON_RELEASE_DEPS_BODY(); }            \
		static type* _instance;                                                \
		std::vector<void (*)()> _deps

/**
 * \def SINGLETON_RELEASE_BODY()
 * The body of release() function.
 */
#define SINGLETON_RELEASE_BODY()                                               \
	if (_instance) {                                                           \
		PINF_3("Releasing");                                                   \
		_instance->releaseDependants();                                        \
		delete _instance;                                                      \
		_instance = NULL;                                                      \
	}                                                                          \
	return

/**constructor
 * \def SINGLETON_RELEASE_DEPS_BODY()
 * The body of releaseDeps() function.
 */
#define SINGLETON_RELEASE_DEPS_BODY()                                          \
	for (unsigned i = 0; i < _deps.size(); i++)                                \
		(*_deps[i])()

/**
 * \def SINGLETON_REGISTRATION(type)
 * Register a singleton object.
 *
 * \note
 * \#include \<SingletonAutoDestructor.h\>
 */
#define SINGLETON_REGISTRATION(type)                                           \
	static cml::SingletonAutoDestructor< type > CONCATE(__autodes, __LINE__);  \
	type* type::_instance = NULL;                                              \
	type* type::instance() {                                                   \
		if (!_instance) {                                                      \
			_instance = new type()

/**
 * \def SINGLETON_DEPENDS(self_type, dep_type)
 * Declare that self_type depends on dep_type. It affects the destruction
 * sequence.
 */
#define SINGLETON_DEPENDS(self_type, dep_type)                                 \
			dep_type::instance()->registerDependant(&self_type::release)

/**
 * \def SINGLETON_DEPENDS_SOCKET(self_type)
 * Declare that self_type depends on socket objects.
 *
 * \note
 * \#include \<AbstractSocket.h\>
 */
#define SINGLETON_DEPENDS_SOCKET(self_type)                                    \
			AbstractSocket::registerSocketDependant(&self_type::release)

/**
 * \def SINGLETON_REGISTRATION_END()
 * The end clause of singleton registration.
 */
#define SINGLETON_REGISTRATION_END()                                           \
		}                                                                      \
		return _instance;                                                      \
	}                                                                          \
	typedef int __DummyTypeDefForSemiColonEnding__

/**
 * Initialize members singleton macros need. It should be put within
 * (and should be the first item in) the initialization list of the constructor.
 */
#define SINGLETON_MEMBER_INITLST \
	_deps()

/**
 * \def PERR(str)
 * Print an error message. str is a stream in "a << b << c" format. It's a
 * multi-line macro.
 *
 * \note
 * \#include \<iostream\> <br>
 * \#include \<sstream\>
 */
#define PERR(msg)                                                              \
{                                                                              \
	std::stringstream __tmpstream;                                             \
	__tmpstream << "Error: " << msg << std::endl << "\t[" <<                   \
	__PRETTY_FUNCTION__ << ": " << __LINE__ << "]";                            \
	pthread_mutex_lock(&g_mxcerr);                                             \
	std::cerr << __tmpstream.str() << std::endl;                               \
	pthread_mutex_unlock(&g_mxcerr);                                           \
}                                                                              \
	typedef int CONCATE(__DummyTypeDefForSemiColonEnding__, __LINE__)


#ifdef DEBUG
#define __PINF(msg)                                                            \
{                                                                              \
	std::stringstream __tmpstream;                                             \
	__tmpstream << msg << std::endl << "\t[" << __PRETTY_FUNCTION__ << ": "    \
	<< __LINE__ << "]";                                                        \
	pthread_mutex_lock(&g_mxcout);                                             \
	std::cout << __tmpstream.str() << std::endl;                               \
	pthread_mutex_unlock(&g_mxcout);                                           \
}                                                                              \
	typedef int CONCATE(__DummyTypeDefForSemiColonEnding__, __LINE__)
#endif /* DEBUG */

#if DEBUG >= 1 // Normal
/**
 * \def PINFO_1(str)
 * Print an info message. str is a stream in "a << b << c" format.
 * Only show when compiled as DEBUG >= 1. It's a multi-line macro.
 *
 * \note
 * \#include \<iostream\> <br>
 * \#include \<sstream\>
 */
#define PINF_1(str) __PINF("Info<1>: " << str)
#else
#define PINF_1(str)
#endif /* DEBUG >= 1 */

#if DEBUG >= 2 // Verbose
/**
 * \def PINFO_2(str)
 * Print an info message. str is a stream in "a << b << c" format.
 * Only show when compiled as DEBUG >= 2 (verbose). It's a multi-line macro.
 *
 * \note
 * \#include \<iostream\> <br>
 * \#include \<sstream\>
 */
#define PINF_2(str) __PINF("Info<2>: " << str)
#else
#define PINF_2(str)
#endif /* DEBUG >= 2 */

#if DEBUG >= 3 // Very verbose
/**
 * \def PINFO_3(str)
 * Print an info message. str is a stream in "a << b << c" format.
 * Only show when compiled as DEBUG >= 3 (very verbose). It's a multi-line
 * macro.
 *
 * \note
 * \#include \<iostream\> <br>
 * \#include \<sstream\>
 */
#define PINF_3(str) __PINF("Info<3>: " << str)
#else
#define PINF_3(str)
#endif /* DEBUG >= 3 */

#endif /* HELPERMACROS_H_ */
