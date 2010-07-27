/**
 * \file MSortFinalizer.h
 * \date Jun 28, 2010
 * \author samael
 */

#ifndef MSORTFINALIZER_H_
#define MSORTFINALIZER_H_

#include <AActor.h>
#include <CFlowVector.h>

class MSortFinalizer: public wolf::AActor
{
public:
	MSortFinalizer(int nports);
	~MSortFinalizer();
	State state();
	void prefire();
	void fire();
	void postfire();
	bool testend();
	uint32_t findmin();

private:
	State _state;
	wolf::CFlowVector<wolf::CFlowVector<uint32_t> *> _vex;
	wolf::CFlowVector<wolf::CFlowVector<uint32_t>::iterator > _its;
};

#endif /* MSORTFINALIZER_H_ */
