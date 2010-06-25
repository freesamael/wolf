/**
 * \file SharedMemory.cpp
 * \date Mar 18, 2010
 * \author samael
 */

#ifdef ENABLE_D2MCE /* DSM mode */
#include <cstring>
#include "SharedMemory.h"
#include "D2MCE.h"

using namespace std;

namespace wfe
{

/**
 * Clone the shared memory. It's done by D2MCE::createSharedMemory().
 */
IDrop* SharedMemory::clone() const
{
	return new SharedMemory(*this);
}

}

#endif /* ENABLE_D2MCE */
