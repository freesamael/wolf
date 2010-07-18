/**
 * \file MansetWorkerCreator.cpp
 * \date Jul 17, 2010
 * \author samael
 */

#include <cstring>
#include <CTlvBlock.h>
#include <CTlvObjectFactory.h>
#include "MansetWorkerCreator.h"
#include "MansetException.h"

using namespace std;
using namespace cml;
using namespace wfe;

ITlvObject* MansetWorkerCreator::create(const ITlvBlock &blk) const
{
	MansetWorker *worker = new MansetWorker();

	uint32_t nbytes;

	memcpy(&nbytes, blk.value(), 4);
	uint32_t imgwidth = ntohl(nbytes);

	memcpy(&nbytes, blk.value() + 4, 4);
	uint32_t imgheight = ntohl(nbytes);

	memcpy(&nbytes, blk.value() + 8, 4);
	uint32_t minrow = ntohl(nbytes);

	memcpy(&nbytes, blk.value() + 12, 4);
	uint32_t rows = ntohl(nbytes);

	worker->setImageRange(imgwidth, imgheight, minrow, rows);

	if (blk.length() > 16)
		worker->setImageData((uint8_t *)(blk.value() + 16), blk.length() - 16);

	return worker;
}
