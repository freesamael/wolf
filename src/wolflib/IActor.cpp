/*
 * IActor.cpp
 *
 *  Created on: Mar 28, 2010
 *      Author: samael
 */

#include "IActor.h"

namespace wfe
{
	/// Use StateString[IActor::state()] to fetch the name of state.
	const char *IActor::StateString[] =
			{"Not Ready", "Ready", "Running", "Finished", "Terminated"};
}
