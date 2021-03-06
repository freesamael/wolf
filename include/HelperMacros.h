/**
 * \file HelperMacros.h
 * This file defines helper macros for wolf.
 */

#ifndef HELPERMACROS_H_
#define HELPERMACROS_H_

#include <pthread.h>
#include "CTime.h"

namespace wolf {
	extern pthread_mutex_t g_mxcout;
	extern pthread_mutex_t g_mxcerr;
	std::string demangle(const char *manglename);
}

#if defined(__DEBUG__) && (defined(__GLIBCXX__) || defined(__clang__))
#define __DEMANGLE__  1
#endif /* defined(__DEBUG__) && (defined(__GLIBCXX__) || defined(__clang__)) */

#define SZ_MSG_MAX	1500

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
 * \#include \<string\>
 */
#define TYPENAME(type) wolf::demangle(typeid(type).name())

/**
 * \def CONCATE(x, y)
 * Concatenate two symbols even they are other macros.
 */
#define CONCATE(x, y) __CONCATE(x, y)
#define __CONCATE(x, y) x##y

/**
 * \def TLV_OBJECT_REGISTRATION(type, id, creator)
 * Register a TLV object to CTlvObjectFactory with given id and creator.
 *
 * \note
 * \#include \<typeinfo\> <br>
 * \#include \<string\> <br>
 * \#include \<CTlvObjectFactoryAutoRegistry.h\>
 */
#define TLV_OBJECT_REGISTRATION(type, id, creator) \
	static wolf::CTlvObjectFactoryAutoRegistry CONCATE(__autoreg, __LINE__)(\
			TYPENAME(type), id, new creator())

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
 * \#include \<CSingletonAutoDestructor.h\>
 */
#define SINGLETON_REGISTRATION(type)                                           \
	static wolf::CSingletonAutoDestructor< type > CONCATE(__autodes, __LINE__); \
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
 * \#include \<ASocket.h\>
 */
#define SINGLETON_DEPENDS_SOCKET(self_type)                                    \
			wolf::ASocket::registerSocketDependant(&self_type::release)

/**
 * \def SINGLETON_REGISTRATION_END()
 * The end clause of singleton registration.
 */
#define SINGLETON_REGISTRATION_END()                                           \
		}                                                                      \
		return _instance;                                                      \
	}                                                                          \
	typedef int __DummyTypeDefForSemiColonEnding__	// For semicolon.

/**
 * Initialize members singleton macros need. It should be put within
 * (and should be the first item in) the initialization list of the constructor.
 */
#define SINGLETON_MEMBER_INITLST \
	_deps()

/**
 * \def PERR(str)
 * Print an error message. str is a stream in "a << b << c" format.
 *
 * \note
 * \#include \<iostream\> <br>
 * \#include \<sstream\>
 */
#define PERR(msg)                                                              \
do {                                                                           \
	std::stringstream __tmpstream;                                             \
	__tmpstream << "Error: " << msg << std::endl << "\t[" <<                   \
	__PRETTY_FUNCTION__ << ": " << __LINE__ << "]";                            \
	pthread_mutex_lock(&g_mxcerr);                                             \
	std::cerr << wolf::CTime::now() << ": " << __tmpstream.str() <<             \
	std::endl;                                                                 \
	pthread_mutex_unlock(&g_mxcerr);                                           \
} while (false) // For semicolon and one-line statement.


#ifdef __DEBUG__
#define __PINF(msg)                                                            \
do {                                                                           \
	std::stringstream __tmpstream;                                             \
	__tmpstream << msg << std::endl << "\t[" << __PRETTY_FUNCTION__ << ": "    \
	<< __LINE__ << "]";                                                        \
	pthread_mutex_lock(&g_mxcout);                                             \
	std::cout << wolf::CTime::now() << ": " << __tmpstream.str() <<             \
	std::endl;                                                                 \
	pthread_mutex_unlock(&g_mxcout);                                           \
} while (false) // For semicolon and one-line statement.
#endif /* __DEBUG__ */

#if __DEBUG__ >= 1 // Normal
/**
 * \def PINFO_1(str)
 * Print an info message. str is a stream in "a << b << c" format.
 * Only show when compiled as __DEBUG__ >= 1.
 *
 * \note
 * \#include \<iostream\> <br>
 * \#include \<sstream\>
 */
#define PINF_1(str) __PINF("Info<1>: " << str)
#else
#define PINF_1(str)
#endif /* __DEBUG__ >= 1 */

#if __DEBUG__ >= 2 // Verbose
/**
 * \def PINFO_2(str)
 * Print an info message. str is a stream in "a << b << c" format.
 * Only show when compiled as __DEBUG__ >= 2 (verbose).
 *
 * \note
 * \#include \<iostream\> <br>
 * \#include \<sstream\>
 */
#define PINF_2(str) __PINF("Info<2>: " << str)
#else
#define PINF_2(str)
#endif /* __DEBUG__ >= 2 */

#if __DEBUG__ >= 3 // Very verbose
/**
 * \def PINFO_3(str)
 * Print an info message. str is a stream in "a << b << c" format.
 * Only show when compiled as __DEBUG__ >= 3 (very verbose).
 *
 * \note
 * \#include \<iostream\> <br>
 * \#include \<sstream\>
 */
#define PINF_3(str) __PINF("Info<3>: " << str)
#else
#define PINF_3(str)
#endif /* __DEBUG__ >= 3 */

#endif /* HELPERMACROS_H_ */
