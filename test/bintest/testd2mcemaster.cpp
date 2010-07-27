/**
 * \file testd2mce.cpp
 * \date Apr 10, 2010
 * \author samael
 */

#include <iostream>
#include <CD2mce.h>
#include <unistd.h>

using namespace std;
using namespace wolf;

int main()
{
#ifdef ENABLE_D2MCE /* DSM mode */
	D2MCE::instance()->join("test");
	cout << "Node ID = " << D2MCE::instance()->nodeId() << endl;

	D2MCE::instance()->barrier(2);

	SharedMemory *sm = D2MCE::instance()->createSharedMemory(sizeof(int));
	cout << "Memory Address = " << hex << (unsigned)sm << endl;
	sm->lock();
	*((int *)sm->buffer()) = 10;
	sm->store();
	sm->unlock();

	D2MCE::instance()->barrier(2);
#endif /* ENABLE_D2MCE */
	return 0;
}
