/**
 * \file MansetWorker.h
 * \date Jul 16, 2010
 * \author samael
 */

#ifndef MANSETWORKER_H_
#define MANSETWORKER_H_

#include <inttypes.h>
#include <AWorkerActor.h>
#include <CFlowUint32.h>

class FlowUint8Pointer: public wfe::IDrop
{
public:
	FlowUint8Pointer(uint8_t *p): _p(p) {}
	FlowUint8Pointer(const FlowUint8Pointer &o): _p(o._p) {}
	IDrop* clone() const { return new FlowUint8Pointer(*this); }

private:
	uint8_t *_p;
};

class MansetWorker: public wfe::AWorkerActor
{
public:
	MansetWorker(): _minx(0), _miny(0), _maxx(0), _maxy(0), _imgwidth(0),
			_imgheight(0), _imgdata(NULL) {}
	void managerInitialization(wfe::IManagerActor *mgr);
	void managerFinalization(wfe::IManagerActor *mgr);
	void managerPrefire(wfe::IManagerActor *mgr);
	void managerPostfire(wfe::IManagerActor *mgr);
	void fire();
	void update(AWorkerActor *o);
	void setImageRange(wfe::CFlowUint32 minx, wfe::CFlowUint32 miny,
			wfe::CFlowUint32 xrange, wfe::CFlowUint32 yrange,
			wfe::CFlowUint32 imgwidth, wfe::CFlowUint32 imgheight);
	void setImageData(uint8_t *imgdata, uint32_t size);
	cml::CTlvBlock* toTLVBlock() const;

private:
	wfe::CFlowUint32 _minx, _miny, _xrange, _yrange, _imgwidth, _imgheight;
	uint8_t *_imgdata;
};

#endif /* MANSETWORKER_H_ */
