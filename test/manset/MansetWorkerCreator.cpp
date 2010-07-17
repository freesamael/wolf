/**
 * \file MansetWorkerCreator.cpp
 * \date Jul 17, 2010
 * \author samael
 */

#include <CTlvBlock.h>
#include <CTlvObjectFactory.h>
#include "MansetWorkerCreator.h"

using namespace cml;
using namespace wfe;

ITlvObject* MansetWorkerCreator::create(const ITlvBlock &blk)
{
	MansetWorker *worker = new MansetWorker();
	unsigned offset = 0;

	CSharedTlvBlock minxblk(blk.value());
	CFlowUint32 *minx;
	if (!(minx = dynamic_cast<CFlowUint32 *>(CTlvObjectFactory::instance()->createTLVObject(minxblk))))
		throw MansetException("Fail to construct minx.");
	offset += minxblk.plainSize();

	CSharedTlvBlock minyblk(blk.value() + offset);
	CFlowUint32 *miny;
	if (!(miny = dynamic_cast<CFlowUint32 *>(CTlvObjectFactory::instance()->createTLVObject(minyblk))))
		throw MansetException("Fail to construct miny.");
	offset += minyblk.plainSize();

	CSharedTlvBlock xrangeblk(blk.value() + offset);
	CFlowUint32 *xrange;
	if (!(xrange = dynamic_cast<CFlowUint32 *>(CTlvObjectFactory::instance()->createTLVObject(xrangeblk))))
		throw MansetException("Fail to construct xrange.");
	offset += xrangeblk.plainSize();

	CSharedTlvBlock yrangeblk(blk.value() + offset);
	CFlowUint32 *yrange;
	if (!(yrange = dynamic_cast<CFlowUint32 *>(CTlvObjectFactory::instance()->createTLVObject(yrangeblk))))
		throw MansetException("Fail to construct yrange.");
	offset += yrangeblk.plainSize();

	CSharedTlvBlock imgwidthblk(blk.value() + offset);
	CFlowUint32 *imgwidth;
	if (!(imgwidth = dynamic_cast<CFlowUint32 *>(CTlvObjectFactory::instance()->createTLVObject(imgwidthblk))))
		throw MansetException("Fail to construct imgwidth.");
	offset += imgwidthblk.plainSize();

	CSharedTlvBlock imgheightblk(blk.value() + offset);
	CFlowUint32 *imgheight;
	if (!(imgheight = dynamic_cast<CFlowUint32 *>(CTlvObjectFactory::instance()->createTLVObject(imgheightblk))))
		throw MansetException("Fail to construct imgheight.");
	offset += imgheightblk.plainSize();

	worker->setImageRange(minx, miny, xrange, yrange, imgwidth, imgheight);
	delete minx;
	delete miny;
	delete xrange;
	delete yrange;
	delete imgwidth;
	delete imgheight;

	if (blk.length() - offset > 0) {
		uint8_t *imgdata = new uint8_t[blk.length() - offset];
		worker->setImageData(imgdata, blk.length() - offset);
		delete [] imgdata;
	}

	return worker;
}
