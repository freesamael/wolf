/**
 * \file IActor.h
 * \date Mar 28, 2010
 * \author samael
 */

#ifndef IACTOR_H_
#define IACTOR_H_

#include <vector>
#include "SourcePort.h"
#include "SinkPort.h"

namespace wfe
{

/**
 * \interface IActor
 *
 * An actor represents an executable. The execution includes three phases -
 * \b setup -> \b iteration -> \b wrapup.
 *
 * The method setup() maps \b setup phase, wrapup() maps \b wrapup phase,
 * reset() maps \b reset phase, and the \b iteration phase is divided into three
 * methods - prefire(), fire(), postfire(), and they are called in order in each
 * iteration. The scheduler use testfire() method to determine when the
 * iteration ends. It's possible that an actor has zero iteration if the actor's
 * testfire() always returns false, and it's usually a bug of actor.
 *
 * Further, the scheduler might call reset() to reset whole execution phase.
 * It depends on the schedule strategy to determine if the execution should be
 * reset or not.
 */
class IActor
{
public:
	/// Actor states.
	typedef enum State {
		NOT_READY,
		READY,
		RUNNING,
		FINISHED,
		TERMINATED
	} State;
	static const char *StateString[];

	virtual ~IActor() {}
	/// Get the state of the actor.
	virtual State state() = 0;
	/// Setup the actor before iteration phase.
	virtual void setup() = 0;
	/// Warp up the actor after iteration phase.
	virtual void wrapup() = 0;
	/// Test if the actor should continue iterate.
	virtual bool testfire() = 0;
	/// Perform preparing actions before each time fire() is called.
	virtual void prefire() = 0;
	/// Actual core execution function of the actor.
	virtual void fire() = 0;
	/// Perform cleanup actions after each time fire() is called.
	virtual void postfire() = 0;
	/// Totally reset the actor as if it's just constructed.
	virtual void reset() = 0;
	/// Get all sink ports.
	virtual const std::vector<SinkPort *>& sinkPorts() = 0;
	/// Get all source ports.
	virtual const std::vector<SourcePort *>& sourcePorts() = 0;
};

}

#endif /* IACTOR_H_ */
