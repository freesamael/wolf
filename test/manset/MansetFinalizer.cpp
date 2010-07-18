/**
 * \file MansetFinalizer.cpp
 * \date Jul 18, 2010
 * \author samael
 */

#include <opencv/cv.h>
#include <opencv/cvaux.h>
#include <opencv/highgui.h>
#include <cstring>
#include "MansetFinalizer.h"
#include "MansetException.h"
#include "MansetWorker.h"

using namespace std;
using namespace wfe;

MansetFinalizer::MansetFinalizer(uint32_t imgwidth, uint32_t imgheight,
		uint32_t rows):
		_state(NOT_READY), _imgwidth(imgwidth), _imgheight(imgheight),
		_rows(rows), _nports(0), _imgdata(NULL)
{
	if (_imgheight % _rows != 0)
		throw MansetException("Must divide exactly.");

	_nports = _imgheight / _rows;
	for (unsigned i = 0; i < _nports; i++)
		addPort(IPort::SINK);
}

MansetFinalizer::~MansetFinalizer()
{
	for (unsigned i = 0; i < _nports; i++)
		removePort(sinkPorts()[0]);
}

void MansetFinalizer::prefire()
{
	_imgdata = new uint8_t *[_nports];
	for (unsigned i = 0; i < _nports; i++) {
		FlowUint8Pointer *p;
		if (!(p = dynamic_cast<FlowUint8Pointer *>(sinkPorts()[i]->readPort())))
			throw MansetException((string)"Invalid flow object." + " (" + __PRETTY_FUNCTION__ + ")");
		_imgdata[i] = p->value();
		delete p;
	}
}

void MansetFinalizer::fire()
{
	IplImage *img = cvCreateImage(cvSize(_imgwidth, _imgheight), IPL_DEPTH_8U, 3);

	for (int i = 0; i < img->height; i++) {
		memcpy((char *)img->imageData,
				(char *)(_imgdata[i / _rows] + (i % _rows) * _imgwidth * 3),
				_imgwidth * 3);
	}

	cvSaveImage("img.jpg", img);
	cvReleaseImage(&img);
	_state = POST_RUNNING;
}

void MansetFinalizer::postfire()
{
	delete [] _imgdata;
}

AActor::State MansetFinalizer::state()
{
	if (_state == NOT_READY) {
		bool ready = true;
		for (unsigned i = 0; i < sinkPorts().size(); i++)
			ready &= !sinkPorts()[i]->isEmpty();
		if (ready)
			_state = READY;
	}
	return _state;
}
