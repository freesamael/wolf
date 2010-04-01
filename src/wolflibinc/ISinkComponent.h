/*
 * ISinkComponent.h
 *
 *  Created on: Mar 28, 2010
 *      Author: samael
 */

#ifndef ISINKCOMPONENT_H_
#define ISINKCOMPONENT_H_

#include <vector>
#include "Port.h"

namespace wfe
{

class ISinkComponent
{
public:
	virtual ~ISinkComponent() {}
	virtual const std::vector<Port *>& inports() = 0;
};

}

#endif /* ISINKCOMPONENT_H_ */
