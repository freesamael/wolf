/**
 * \file IDrop.h
 * \date Apr 12, 2010
 * \author samael
 */

#ifndef IDROP_H_
#define IDROP_H_

namespace wolf
{

/**
 * \interface IDrop
 *
 * A drop indicates an atomic object within the flow which travels between
 * actors, ports and channels. IDrop defines the interface for all drop objects.
 */
class IDrop
{
public:
	virtual ~IDrop() {}
	/// Clones the object itself. It's used when a channel is connected to
	/// multiple sink ports, and needs to produce multiple copies of incoming
	/// objects for sink ports.
	virtual IDrop* clone() const = 0;
};

}

#endif /* IDROP_H_ */
