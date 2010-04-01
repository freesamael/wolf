/*
 * testactors.h
 *
 *  Created on: Apr 1, 2010
 *      Author: samael
 */

#ifndef TESTACTORS_H_
#define TESTACTORS_H_

#include <iostream>
#include <AbstractWorkerActor.h>
#include <TLVBlock.h>
#include <ITLVObjectCreator.h>
#include <TLVObjectFactory.h>

#define TLV_TYPE_TEST_ACTOR		11

class TestActor: public wfe::AbstractWorkerActor
{
public:
	TestActor():_cond(true) {}
	void prefire() {}
	void fire() { std::cout << "Fire!" << std::endl; _cond = false; }
	void postfire() {}
	void reset() {}
	wfe::IActor::State state() { return wfe::IActor::READY; }
	bool firecond() const { return _cond; }
	cml::TLVBlock* toTLVBlock() const {
		return new cml::TLVBlock(TLV_TYPE_TEST_ACTOR, 16);
	}

private:
	bool _cond;
};

class TestActorCreator: public cml::ITLVObjectCreator
{
public:
	cml::ITLVObject* create() const { return new TestActor(); }
	cml::ITLVObject* create(const cml::ITLVBlock &blk) const {
		if (blk.length() == 16)
			return new TestActor();
		return NULL;
	}
};

#endif /* TESTACTORS_H_ */
