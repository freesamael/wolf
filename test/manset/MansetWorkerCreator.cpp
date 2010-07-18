/**
 * \file MansetWorkerCreator.cpp
 * \date Jul 17, 2010
 * \author samael
 */

#include <CTlvBlock.h>
#include <CTlvObjectFactory.h>
#include "MansetWorkerCreator.h"
#include "MansetException.h"

using namespace cml;
using namespace wfe;

ITlvObject* MansetWorkerCreator::create(const ITlvBlock &blk) const
{
	MansetWorker *worker = new MansetWorker();
	unsigned offset = 0;

	uint32_t minx = ntohl((uint32_t)(blk.value()[0]));
	uint32_t miny = ntohl((uint32_t)(blk.value()[4]));
	uint32_t xrange = ntohl((uint32_t)(blk.value()[4 * 2]));
	uint32_t yrange = ntohl((uint32_t)(blk.value()[4 * 3]));
	uint32_t imgwidth = ntohl((uint32_t)(blk.value()[4 * 4]));
	uint32_t imgheight = ntohl((uint32_t)(blk.value()[4 * 5]));
	worker->setImageRange(minx, miny, xrange, yrange, imgwidth, imgheight);

	if (blk.length() > 24)
		worker->setImageData((uint8_t *)(blk.value() + 24), blk.length() - 24);

	return worker;
}
