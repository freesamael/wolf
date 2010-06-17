/**
 * \file HelperMacros.h
 * This file defines helper macros for wolf.
 */

#ifndef HELPERMACROS_H_
#define HELPERMACROS_H_

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
	static cml::TLVObjectFactoryAutoRegistry CONCATE(autoreg, __LINE__)( \
			typeid(type).name(), id, new creator())

/**
 * \def SINGLETON(type)
 * Declare a singleton type. The class should have a private default constructor
 * and should put SINGLETON_MEM_INITLST within the member initialization list.
 *
 * \note
 * \#include \<vector\> <br>
 * \#include \<iostream\>
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
		PINF_3("Releasing");                                                    \
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
	static cml::SingletonAutoDestructor< type > CONCATE(autodes, __LINE__);    \
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
	typedef int DummyTypeDefForSemiColonEnding__

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
 * \#include \<iostream\>
 */
#define PERR(str) \
	std::cerr << "<error> " << str << ": " << __PRETTY_FUNCTION__ << ": " \
	<< __LINE__ << std::endl

#ifdef DEBUG
#define __PINF(str) \
	std::cout << str << ": " << __PRETTY_FUNCTION__ << ": " \
	<< __LINE__ << std::endl

#if DEBUG >= 1 // Normal
/**
 * \def PINFO_1(str)
 * Print an info message. str is a stream in "a << b << c" format.
 * Only show when compiled as DEBUG >= 1.
 *
 * \note
 * \#include \<iostream\>
 */
#define PINF_1(str) __PINF("<info_1> " << str)
#endif /* DEBUG >= 1 */

#if DEBUG >= 2 // Verbose
/**
 * \def PINFO_2(str)
 * Print an info message. str is a stream in "a << b << c" format.
 * Only show when compiled as DEBUG >= 2 (verbose).
 *
 * \note
 * \#include \<iostream\>
 */
#define PINF_2(str) __PINF(std::tab << "<info_2> " << str)
#endif /* DEBUG >= 2 */

#if DEBUG >= 3 // Very verbose
/**
 * \def PINFO_3(str)
 * Print an info message. str is a stream in "a << b << c" format.
 * Only show when compiled as DEBUG >= 3 (very verbose).
 *
 * \note
 * \#include \<iostream\>
 */
#define PINF_3(str) __PINF(std::tab << std::tab << "<info_3> " << str)
#endif /* DEBUG >= 3 */
#else
#define PINF_1(str)
#define PINF_2(str)
#define PINF_3(str)
#endif /* DEBUG */



#endif /* HELPERMACROS_H_ */
