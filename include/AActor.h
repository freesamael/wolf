/**
 * \file AActor.h
 * \date Mar 28, 2010
 * \author samael
 */

#ifndef AACTOR_H_
#define AACTOR_H_

#include <string>
#include <vector>
#include "CSourcePort.h"
#include "CSinkPort.h"

namespace wolf
{

/**
 * An actor represents an executable. An execution includes three phases -
 * \b setup -> \b iteration -> \b wrapup.
 *
 * The method setup() maps \b setup phase, wrapup() maps \b wrapup phase,
 * reset() maps \b reset phase, and the \b iteration phase is divided into three
 * methods - prefire(), fire(), postfire(), and they are called in order in each
 * iteration. The scheduler use testfire() method to determine when the
 * iteration ends. Since an actor should be executed at least once when it's
 * \e ready, it's guaranteed that the actor will be executed even if testfire()
 * always return false, and in this case it's executed exactly once within an
 * execution.
 *
 * Further, the scheduler might call reset() to reset whole execution. It
 * depends on the schedule strategy to determine if the execution should be
 * reset or not.
 */
class AActor
{
public:
	/// Actor states.
	typedef enum State {
		NOT_READY,
		READY,
		RUNNING,
		POST_RUNNING,
		FINISHED,
		TERMINATED
	} State;
	/// Name of states in string.
	static const std::string StateString[];
	AActor(): _sinkp(), _srcp() {}
	virtual ~AActor() {}
	/// Get the state of the actor.
	virtual State state() = 0;
	/// Setup the actor before iteration phase.
	/// The default implementation is empty.
	virtual void setup() {};
	/// Warp up the actor after iteration phase.
	/// The default implementation is empty.
	virtual void wrapup() {};
	/// Test if the actor should continue iterate.
	/// the default implementation always returns false.
	virtual bool testfire() { return false; }
	/// Perform preparing actions before each time fire() is called.
	/// The default implementation is empty.
	virtual void prefire() {}
	/// Actual core execution function of the actor. No default implementation.
	virtual void fire() = 0;
	/// Perform cleanup actions after each time fire() is called.
	/// The default implementation is empty.
	virtual void postfire() {}
	/// Totally reset the actor as if it's just constructed.
	/// The default implementation is empty.
	virtual void reset() {}
	/// Get all sink ports.
	inline virtual const std::vector<CSinkPort *>& sinkPorts() const
			{ return _sinkp; }
	/// Get all source ports.
	inline virtual const std::vector<CSourcePort *>& sourcePorts() const
			{ return _srcp; }
	/// Add a port and return the port added.
	virtual IPort* addPort(IPort::Type type);
	/// Remove and delete (free) a port from the actor.
	/// It takes no effect if the port was not a part of the actor.
	virtual void removePort(IPort *port);

private:
	std::vector<CSinkPort *> _sinkp;
	std::vector<CSourcePort *> _srcp;
};

}

#endif /* AACTOR_H_ */
