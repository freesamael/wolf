/**
 * \file ISinkComponent.h
 * \date Mar 28, 2010
 * \author samael
 */

#ifndef ISINKCOMPONENT_H_
#define ISINKCOMPONENT_H_

#include <vector>
#include "SinkPort.h"

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
	/// Add a sink port and return the port added.
	virtual SinkPort* addSinkPort() = 0;
	/// Get all sink ports.
	virtual const std::vector<SinkPort *>& sinkPorts() = 0;
};

}

#endif /* ISINKCOMPONENT_H_ */
