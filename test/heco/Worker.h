/**
 * \file Worker.h
 * \date Jun 20, 2010
 * \author samael
 */

#ifndef WORKER_H_
#define WORKER_H_

#include <AbstractWorkerActor.h>
#include <DUInt32.h>

class Worker: public wfe::AbstractWorkerActor
{
public:
	Worker() { addPort(wfe::IPort::SINK); addPort(wfe::IPort::SOURCE); }
	~Worker() { delete sinkPorts()[0]; delete sourcePorts()[0]; }
	void managerPrefire(wfe::ManagerActor *manager);
	void managerPostfire(wfe::ManagerActor *manager);
	void fire();
	void setNum(wfe::DUInt32 n) { _n = n; }
	cml::StandardTLVBlock* toTLVBlock() const;

private:
	wfe::DUInt32 _n;
};

#endif /* WORKER_H_ */
