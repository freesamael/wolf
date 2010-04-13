/**
 * \file IActor.cpp
 * \date Mar 28, 2010
 * \author samael
 */

#include "IActor.h"

namespace wfe
{
	/// Use StateString[IActor::state()] to fetch the name of state.
	const char *IActor::StateString[] =
			{"Not Ready", "Ready", "Running", "Finished", "Terminated"};
}
