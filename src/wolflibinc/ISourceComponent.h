/*
 * ISourceComponent.h
 *
 *  Created on: Mar 28, 2010
 *      Author: samael
 */

#ifndef ISOURCECOMPONENT_H_
#define ISOURCECOMPONENT_H_

#include <vector>
#include "Port.h"

namespace wfe
{

class ISourceComponent
{
public:
	virtual ~ISourceComponent() {}
	virtual const std::vector<Port *>& outports() = 0;
};

}

#endif /* ISOURCECOMPONENT_H_ */
