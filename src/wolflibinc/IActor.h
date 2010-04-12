#ifndef IACTOR_H_
#define IACTOR_H_

namespace wfe
{

/**
 * \interface IActor
 *
 * Represents all actor object that can be executed.
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
	virtual State state() = 0;
//	virtual void setup();
	virtual void prefire() = 0;
	virtual void fire() = 0;
	virtual void postfire() = 0;
//	virtual void wrapup() = 0;
	virtual void reset() = 0;
};

}

#endif /* IACTOR_H_ */
