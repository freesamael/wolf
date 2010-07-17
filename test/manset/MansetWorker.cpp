/**
 * \file MansetWorker.cpp
 * \date Jul 16, 2010
 * \author samael
 */

#include <vector>
#include <cstring>
#include <CSimpleManagerActor.h>
#include "MansetWorker.h"
#include "MansetException.h"

using namespace std;
using namespace cml;
using namespace wfe;

void MansetWorker::managerInitialization(wfe::IManagerActor *mgr)
{
	CSimpleManagerActor *smgr;
	if (!(smgr = dynamic_cast<CSimpleManagerActor *>(mgr)))
		throw MansetException("Manager must be CSimpleManagerActor.");

	smgr->addPort(IPort::SINK);
	smgr->addPort(IPort::SOURCE);
}

void MansetWorker::managerFinalization(wfe::IManagerActor *mgr)
{
	CSimpleManagerActor *smgr;
	if (!(smgr = dynamic_cast<CSimpleManagerActor *>(mgr)))
		throw MansetException("Manager must be CSimpleManagerActor.");

	smgr->removePort(smgr->sinkPorts()[0]);
	smgr->removePort(smgr->sourcePorts()[0]);
}

void MansetWorker::managerPrefire(wfe::IManagerActor *mgr)
{
	CSimpleManagerActor *smgr;
	if (!(smgr = dynamic_cast<CSimpleManagerActor *>(mgr)))
		throw MansetException("Manager must be CSimpleManagerActor.");

	// Min X
	CFlowUint32 *u32;
	if (!(u32 = dynamic_cast<CFlowUint32 *>(smgr->sinkPorts[0])))
		throw MansetException("Invalid flow object.");
	_minx = *u32;
	delete u32;

	// Min Y
	CFlowUint32 *u32;
	if (!(u32 = dynamic_cast<CFlowUint32 *>(smgr->sinkPorts[0])))
		throw MansetException("Invalid flow object.");
	_miny = *u32;
	delete u32;

	// X Range
	CFlowUint32 *u32;
	if (!(u32 = dynamic_cast<CFlowUint32 *>(smgr->sinkPorts[0])))
		throw MansetException("Invalid flow object.");
	_xrange = *u32;
	delete u32;

	// Y Range
	CFlowUint32 *u32;
	if (!(u32 = dynamic_cast<CFlowUint32 *>(smgr->sinkPorts[0])))
		throw MansetException("Invalid flow object.");
	_yrange = *u32;
	delete u32;

	// Image Width
	CFlowUint32 *u32;
	if (!(u32 = dynamic_cast<CFlowUint32 *>(smgr->sinkPorts[0])))
		throw MansetException("Invalid flow object.");
	_imgwidth = *u32;
	delete u32;

	// Image Height
	CFlowUint32 *u32;
	if (!(u32 = dynamic_cast<CFlowUint32 *>(smgr->sinkPorts[0])))
		throw MansetException("Invalid flow object.");
	_imgheight = *u32;
	delete u32;
}

void MansetWorker::managerPostfire(wfe::IManagerActor *mgr)
{
	CSimpleManagerActor *smgr;
	if (!(smgr = dynamic_cast<CSimpleManagerActor *>(mgr)))
		throw MansetException("Manager must be CSimpleManagerActor.");

	CFlowUint32 *minx = new CFlowUint32(_minx), *miny = new CFlowUint32(_miny),
			*xrange = new CFlowUint32(_xrange),
			*yrange = new CFlowUint32(_yrange);
	FlowUint8Pointer *imgdata = new CFlowUint8Pointer(_imgdata);
	smgr->sourcePorts()[0]->writeChannel(minx);
	smgr->sourcePorts()[0]->writeChannel(miny);
	smgr->sourcePorts()[0]->writeChannel(xrange);
	smgr->sourcePorts()[0]->writeChannel(yrange);
	smgr->sourcePorts()[0]->writeChannel(imgdata);
}

void MansetWorker::fire()
{
	for (unsigned x = _minx; x < _minx + _xrange; x++) {
		for (unsigned y = _miny; y < _miny + _yrange; y++) {
			for (int ch = 0; ch < 3; ch++) {
				double minreal = -2.0;
				double maxreal = 1.0;
				double minimag = -1.2;
				double maximag = 1.2;
				double creal = minreal + x * (maxreal - minreal) / (_imgwidth - 1);
				double cimag = maximag - y * (maximag - minimag) / (_imgheight - 1);
				double zreal = creal, zimag = cimag;
				unsigned maxiter = 1000, iter;
				for (iter = 0; iter < maxiter; iter++) {
					if (zreal * zreal + zimag * zimag > 4)
						break;
					double tmpzreal = zreal * zreal - zimag * zimag;
					zimag = 2 * zreal * zimag + cimag;
					zreal = tmpzreal + creal;
				}
				unsigned index = (y - _miny) * _xrange + (x - _minx) * 3 + ch;
				if (iter == maxiter) {
					_imgdata[index] = 0;
				} else if (ch == 0) {
					if (iter <= 5)
						_imgdata[index] = 50 + iter * 5;
					if (iter <= 15)
						_imgdata[index] = (200 - 75) * (iter - 5) / 10 + 75;
					if (iter <= 20)
						_imgdata[index] = (255 - 200) * (iter - 15) / 5 + 200;
					_imgdata[index] = 255;
				} else if (ch == 1) {
					if (iter <= 13)
						_imgdata[index] = 0;
					if (iter <= 18)
						_imgdata[index] = (iter - 13) * 5;
					if (iter <= 23)
						_imgdata[index] = (255 - 75) * (iter - 18) / 5 + 75;
					_imgdata[index] = 255;
				} else {
					if (iter <= 18)
						_imgdata[index] = 0;
					if (iter <= 20)
						_imgdata[index] = (iter - 18) * 40;
					if (iter <= 23)
						_imgdata[index] = (255 - 80) * (iter - 20) / 3;
					_imgdata[index] = 255;
				}
			}
		}
	}
}
void MansetWorker::update(AWorkerActor *o)
{
	if (o != this) {
		_minx = o._minx;
		_miny = o._miny;
		_xrange = o._xrange;
		_yrange = o._yrange;
		_imgwidth = o._imgwidth;
		_imgheight = o._imgheight;

		unsigned imgsize = _xrange * _yrange;
		delete _imgdata;
		_imgdata = new uint8_t[imgsize];
		memcpy((char*)_imgdata, (char*)o._imgdata, imgsize);
	}
}

void MansetWorker::setImageRange(wfe::CFlowUint32 minx, wfe::CFlowUint32 miny,
		wfe::CFlowUint32 xrange, wfe::CFlowUint32 yrange,
		wfe::CFlowUint32 imgwidth, wfe::CFlowUint32 imgheight)
{
	_minx = minx;
	_miny = miny;
	_xrange = xrange;
	_yrange = yrange;
	_imgwidth = imgwidth;
	_imgheight = imgheight;
}

void MansetWorker::setImageData(uint8_t *imgdata, uint32_t size)
{
	delete _imgdata;
	_imgdata = new uint8_t[size];
	memcpy((char *)_imgdata, (char *)imgdata, size);
}

CTlvBlock* MansetWorker::toTLVBlock() const
{
	vector<const ITlvBlock *> blks;
	blks.push_back(_minx.toTLVBlock());
	blks.push_back(_miny.toTLVBlock());
	blks.push_back(_xrange.toTLVBlock());
	blks.push_back(_yrange.toTLVBlock());
	blks.push_back(_imgwidth.toTLVBlock());
	blks.push_back(_imgheight.toTLVBlock());

	if (_imgdata) {

	}
}
