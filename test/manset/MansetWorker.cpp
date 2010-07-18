/**
 * \file MansetWorker.cpp
 * \date Jul 16, 2010
 * \author samael
 */

#include <vector>
#include <cstring>
//#include <opencv/cv.h>
//#include <opencv/cvaux.h>
//#include <opencv/highgui.h>
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

	CFlowUint32 *u32;

	// Image Width
	if (!(u32 = dynamic_cast<CFlowUint32 *>(smgr->sinkPorts()[0]->readPort())))
		throw MansetException((string)"Invalid flow object." + " (" + __PRETTY_FUNCTION__ + ")");
	_imgwidth = u32->value();
	delete u32;

	// Image Height
	if (!(u32 = dynamic_cast<CFlowUint32 *>(smgr->sinkPorts()[0]->readPort())))
		throw MansetException((string)"Invalid flow object." + " (" + __PRETTY_FUNCTION__ + ")");
	_imgheight = u32->value();
	delete u32;

	// Min Row
	if (!(u32 = dynamic_cast<CFlowUint32 *>(smgr->sinkPorts()[0]->readPort())))
		throw MansetException((string)"Invalid flow object." + " (" + __PRETTY_FUNCTION__ + ")");
	_minrow = u32->value();
	delete u32;

	// Rows
	if (!(u32 = dynamic_cast<CFlowUint32 *>(smgr->sinkPorts()[0]->readPort())))
		throw MansetException((string)"Invalid flow object." + " (" + __PRETTY_FUNCTION__ + ")");
	_rows = u32->value();
	delete u32;
}

void MansetWorker::managerPostfire(wfe::IManagerActor *mgr)
{
	CSimpleManagerActor *smgr;
	if (!(smgr = dynamic_cast<CSimpleManagerActor *>(mgr)))
		throw MansetException("Manager must be CSimpleManagerActor.");

	FlowUint8Pointer *imgdata = new FlowUint8Pointer(_imgdata);
	smgr->sourcePorts()[0]->writeChannel(imgdata);
}

void MansetWorker::prefire()
{
	_imgdata = new uint8_t[_rows * _imgwidth * 3];
}

void MansetWorker::fire()
{
	double minreal = -2.0;
	double maxreal = 1.0;
	double minimag = -1.2;
	double maximag = 1.2;
	double realfactor = (maxreal - minreal) / (_imgwidth - 1);
	double imagfactor = (maximag - minimag) / (_imgheight - 1);
	for (unsigned y = _minrow; y < _minrow + _rows; y++) {
		for (unsigned x = 0; x < _imgwidth; x++) {
			double creal = minreal + x * realfactor;
			double cimag = maximag - y * imagfactor;
			double zreal = creal, zimag = cimag;
			unsigned maxiter = 1000, iter;
			for (iter = 0; iter < maxiter; iter++) {
				if (zreal * zreal + zimag * zimag > 4)
					break;
				double tmpzreal = zreal * zreal - zimag * zimag;
				zimag = 2 * zreal * zimag + cimag;
				zreal = tmpzreal + creal;
			}
			for (int ch = 0; ch < 3; ch++) {
				unsigned index = (y - _minrow) * (_imgwidth * 3) + x * 3 + ch;
				if (iter == maxiter) {
					_imgdata[index] = 0;
				} else if (ch == 0) {
					if (iter <= 5)
						_imgdata[index] = 50 + iter * 5;
					else if (iter <= 15)
						_imgdata[index] = (200 - 75) * (iter - 5) / 10 + 75;
					else if (iter <= 20)
						_imgdata[index] = (255 - 200) * (iter - 15) / 5 + 200;
					else
						_imgdata[index] = 255;
				} else if (ch == 1) {
					if (iter <= 13)
						_imgdata[index] = 0;
					else if (iter <= 18)
						_imgdata[index] = (iter - 13) * 5;
					else if (iter <= 23)
						_imgdata[index] = (255 - 75) * (iter - 18) / 5 + 75;
					else
						_imgdata[index] = 255;
				} else {
					if (iter <= 18)
						_imgdata[index] = 0;
					else if (iter <= 20)
						_imgdata[index] = (iter - 18) * 40;
					else if (iter <= 23)
						_imgdata[index] = (255 - 80) * (iter - 20) / 3;
					else
						_imgdata[index] = 255;
				}
			}
		}
	}
}

void MansetWorker::postfire()
{
//	IplImage *img = cvCreateImage(cvSize(_imgwidth, _rows), IPL_DEPTH_8U, 3);
//
//	for (int i = 0; i < img->height; i++) {
//		memcpy(img->imageData, _imgdata, _imgwidth * 3);
//	}
//	img->imageData = (char *)_imgdata;
//
//	char nstr[10];
//	sprintf(nstr, "%d", _minrow);
//	string filename = (string)"img_" + nstr + ".jpg";
//	cvSaveImage(filename.c_str(), img);
//	cvReleaseImage(&img);
}

void MansetWorker::update(AWorkerActor *o)
{
	if (o != this) {
		MansetWorker *w;
		if (!(w = dynamic_cast<MansetWorker *>(o)))
			throw MansetException("Invalid object for updating.");
		_imgwidth = w->_imgwidth;
		_imgheight = w->_imgheight;
		_minrow = w->_minrow;
		_rows = w->_rows;

		unsigned imgsize = _rows * _imgwidth * 3;
		delete _imgdata;
		_imgdata = new uint8_t[imgsize];
		memcpy((char*)_imgdata, (char*)w->_imgdata, imgsize);
	}
}

void MansetWorker::setImageRange(uint32_t imgwidth, uint32_t imgheight,
		uint32_t minrow, uint32_t rows)
{
	_imgwidth = imgwidth;
	_imgheight = imgheight;
	_minrow = minrow;
	_rows = rows;
}

void MansetWorker::setImageData(uint8_t *imgdata, uint32_t size)
{
	delete _imgdata;
	_imgdata = new uint8_t[size];
	memcpy((char *)_imgdata, (char *)imgdata, size);
}

CTlvBlock* MansetWorker::toTLVBlock() const
{
	uint16_t size = 16; // four uint32_t
	if (_imgdata)
		size += _rows * _imgwidth * 3;

	CTlvBlock *blk = new CTlvBlock(TLV_TYPE_WORKER, size);

	uint32_t nbytes = htonl(_imgwidth);
	memcpy(blk->value(), (char *)&nbytes, 4);

	nbytes = htonl(_imgheight);
	memcpy(blk->value() + 4, (char *)&nbytes, 4);

	nbytes = htonl(_minrow);
	memcpy(blk->value() + 8, (char *)&nbytes, 4);

	nbytes = htonl(_rows);
	memcpy(blk->value() + 12, (char *)&nbytes, 4);

	if (_imgdata)
		memcpy(blk->value() + 16, _imgdata, _rows * _imgwidth * 3);

	return blk;
}
