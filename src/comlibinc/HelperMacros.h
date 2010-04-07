/*
 * HelperMacros.h
 *
 *  Created on: Apr 7, 2010
 *      Author: samael
 */

#ifndef HELPERMACROS_H_
#define HELPERMACROS_H_

#define CONCATE(x, y) __CONCATE(x, y)
#define __CONCATE(x, y) x##y

#define TLV_OBJECT_REGISTRATION( type, id, creator ) \
	static cml::TLVObjectFactoryAutoRegistor CONCATE(autoreg, __LINE__)( \
			typeid(type).name(), id, new creator() )

#define SINGLETON_REGISTRATION( type ) \
	static cml::SingletonAutoDestructor< type > CONCATE(autodes, __LINE__)

#endif /* HELPERMACROS_H_ */
