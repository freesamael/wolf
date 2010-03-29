/*
 * TLVMessage.cpp
 *
 *  Created on: Mar 29, 2010
 *      Author: samael
 */

#include <cstdio>
#include "TLVMessage.h"

using namespace cml;

namespace wfe
{

void TLVMessage::run()
{
	switch (_cmd) {
	case INVALID:
		fprintf(stderr, "TLVMessage::run(): Error: INVALID command can not be run.\n");
		break;
	case ADD_MASTER:
		break;
	case ADD_SLAVE:
		break;
	case RUN_ACTOR:
		break;
	default:
		fprintf(stderr, "TLVMessage::run(): Error: Unrecognized command.\n");
	}
}

TLVBlock* TLVMessage::toTLVBlock() const
{
	return NULL;
}

}
