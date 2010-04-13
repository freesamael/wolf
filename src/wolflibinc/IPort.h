/**
 * \file IPort.h
 * \date Apr 12, 2010
 * \author samael
 */

#ifndef IPORT_H_
#define IPORT_H_

namespace wfe
{

class Channel;
class IActor;

/**
 * \interface IPort
 *
 * Defines the interface for input/output ports.
 */
class IPort
{
public:
	virtual ~IPort() {}
	virtual IActor* owner() const = 0; ///< Get the owner of this port.
	virtual Channel* channel() const = 0; ///< Get the channel attached.
	virtual void setChannel(Channel *ch) = 0; ///< Set the attached channel.
};

}

#endif /* IPORT_H_ */
