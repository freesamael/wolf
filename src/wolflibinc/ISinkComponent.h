#ifndef ISINKCOMPONENT_H_
#define ISINKCOMPONENT_H_

#include <vector>
#include "Port.h"

namespace wfe
{

/**
 * \interface ISinkComponent
 *
 * Represents all objects with input ports.
 */
class ISinkComponent
{
public:
	virtual ~ISinkComponent() {}
	virtual const std::vector<Port *>& inports() = 0;
};

}

#endif /* ISINKCOMPONENT_H_ */
