/**
 * \file IPort.h
 * \date Apr 12, 2010
 * \author samael
 */

#ifndef IPORT_H_
#define IPORT_H_

#include <string>

namespace wolf
{

class CChannel;
class AActor;

/**
 * \interface IPort
 *
 * Defines the interface for input/output ports.
 */
class IPort
{
public:
	/// IO type of the port.
	typedef enum Type {
		SINK,
		SOURCE
	} Type;
	/// Name of types in string.
	static const std::string TypeString[];
	virtual ~IPort() {}
	virtual Type type() const = 0;
	virtual AActor* owner() const = 0; ///< Get the owner of this port.
	virtual CChannel* channel() const = 0; ///< Get the channel attached.
	virtual void setChannel(CChannel *ch) = 0; ///< Set the attached channel.
};

}

#endif /* IPORT_H_ */
