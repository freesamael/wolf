/**
 * \file HelloWorker.h
 * \date Apr 14, 2010
 * \author samael
 */

#ifndef HELLOWORKER_H_
#define HELLOWORKER_H_

#include <iostream>
#include <AbstractWorkerActor.h>

class HelloWorker: public wfe::AbstractWorkerActor
{
public:
	void fire() { std::cout << "Hello World!" << std::endl; }
	cml::StandardTLVBlock* toTLVBlock() const;
};

#endif /* HELLOWORKER_H_ */
