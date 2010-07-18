/**
 * \file MansetWorker.cpp
 * \date Jul 16, 2010
 * \author samael
 */

#include <vector>
#include <cstring>
#include <arpa/inet.h>
#include <CSimpleManagerActor.h>
#include <CTlvObjectFactoryAutoRegistry.h>
#include <HelperMacros.h>
#include "MansetWorker.h"
#include "MansetException.h"
#include "MansetWorkerCreator.h"

using namespace std;
using namespace cml;
using namespace wfe;

#define TLV_TYPE_WORKER 130
TLV_OBJECT_REGISTRATION(MansetWorker, TLV_TYPE_WORKER, MansetWorkerCreator);

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
	if (!(u32 = dynamic_cast<CFlowUint32 *>(smgr->sinkPorts()[0])))
		throw MansetException("Invalid flow object.");
	_minx = u32->value();
	delete u32;

	// Min Y
	if (!(u32 = dynamic_cast<CFlowUint32 *>(smgr->sinkPorts()[0])))
		throw MansetException("Invalid flow object.");
	_miny = u32->value();
	delete u32;

	// X Range
	if (!(u32 = dynamic_cast<CFlowUint32 *>(smgr->sinkPorts()[0])))
		throw MansetException("Invalid flow object.");
	_xrange = u32->value();
	delete u32;

	// Y Range
	if (!(u32 = dynamic_cast<CFlowUint32 *>(smgr->sinkPorts()[0])))
		throw MansetException("Invalid flow object.");
	_yrange = u32->value();
	delete u32;

	// Image Width
	if (!(u32 = dynamic_cast<CFlowUint32 *>(smgr->sinkPorts()[0])))
		throw MansetException("Invalid flow object.");
	_imgwidth = u32->value();
	delete u32;

	// Image Height
	if (!(u32 = dynamic_cast<CFlowUint32 *>(smgr->sinkPorts()[0])))
		throw MansetException("Invalid flow object.");
	_imgheight = u32->value();
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
	FlowUint8Pointer *imgdata = new FlowUint8Pointer(_imgdata);
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
		MansetWorker *w;
		if (!(w = dynamic_cast<MansetWorker *>(o)))
			throw MansetException("Invalid object for updating.");
		_minx = w->_minx;
		_miny = w->_miny;
		_xrange = w->_xrange;
		_yrange = w->_yrange;
		_imgwidth = w->_imgwidth;
		_imgheight = w->_imgheight;

		unsigned imgsize = _xrange * _yrange;
		delete _imgdata;
		_imgdata = new uint8_t[imgsize];
		memcpy((char*)_imgdata, (char*)w->_imgdata, imgsize);
	}
}

void MansetWorker::setImageRange(uint32_t minx, uint32_t miny,
		uint32_t xrange, uint32_t yrange,
		uint32_t imgwidth, uint32_t imgheight)
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
	uint16_t size = 24; // six uint32_t
	if (_imgdata)
		size += _xrange * _yrange;

	CTlvBlock *blk = new CTlvBlock(TLV_TYPE_WORKER, size);

	uint32_t nbytes = htonl(_minx);
	memcpy(blk->value(), (char *)&nbytes, 4);

	nbytes = htonl(_miny);
	memcpy(blk->value() + 4, (char *)&nbytes, 4);

	nbytes = htonl(_xrange);
	memcpy(blk->value() + 8, (char *)&nbytes, 4);

	nbytes = htonl(_yrange);
	memcpy(blk->value() + 12, (char *)&nbytes, 4);

	nbytes = htonl(_imgwidth);
	memcpy(blk->value() + 16, (char *)&nbytes, 4);

	nbytes = htonl(_imgheight);
	memcpy(blk->value() + 20, (char *)&nbytes, 4);

	if (_imgdata)
		memcpy(blk->value() + 24, _imgdata, _xrange * _yrange);

	return blk;
}
