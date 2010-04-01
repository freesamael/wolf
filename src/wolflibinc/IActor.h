/*
 * IActor.h
 *
 *  Created on: Mar 28, 2010
 *      Author: samael
 */

#ifndef IACTOR_H_
#define IACTOR_H_

namespace wfe
{

class IActor
{
public:
	typedef enum State {
		NOT_READY,
		READY,
		RUNNING,
		FINISH
	} State;
	static const char *StateString[];

	virtual ~IActor() {}
	virtual State state() = 0;
	virtual void prefire() = 0;
	virtual void fire() = 0;
	virtual void postfire() = 0;
	virtual void reset() = 0;
};

}

#endif /* IACTOR_H_ */
