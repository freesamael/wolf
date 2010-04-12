#ifndef ISOURCECOMPONENT_H_
#define ISOURCECOMPONENT_H_

#include <vector>
#include "Port.h"

namespace wfe
{

/**
 * \interface ISourceComponent
 *
 * Represents all objects with output ports.
 */
class ISourceComponent
{
public:
	virtual ~ISourceComponent() {}
	virtual const std::vector<Port *>& outports() = 0;
};

}

#endif /* ISOURCECOMPONENT_H_ */
