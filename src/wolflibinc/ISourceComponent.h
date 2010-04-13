/**
 * \file ISourceComponent.h
 * \date Mar 28, 2010
 * \author samael
 */

#ifndef ISOURCECOMPONENT_H_
#define ISOURCECOMPONENT_H_

#include <vector>
#include "SourcePort.h"

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
	/// Add a source port and return the port added.
	virtual SourcePort* addSourcePort() = 0;
	/// Get all source ports.
	virtual const std::vector<SourcePort *>& sourcePorts() = 0;
};

}

#endif /* ISOURCECOMPONENT_H_ */
