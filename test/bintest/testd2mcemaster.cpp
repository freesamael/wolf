/**
 * \file testd2mce.cpp
 * \date Apr 10, 2010
 * \author samael
 */

#include <iostream>
#include <D2MCE.h>
#include <unistd.h>

using namespace std;
using namespace wfe;

int main()
{
#ifndef DISABLE_D2MCE
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
#endif
	return 0;
}
