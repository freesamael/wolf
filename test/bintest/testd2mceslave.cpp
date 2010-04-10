/*
 * testd2mce.cpp
 *
 *  Created on: Apr 10, 2010
 *      Author: samael
 */

#include <iostream>
#include <D2MCE.h>
#include <unistd.h>

using namespace std;
using namespace cml;

int main()
{
	D2MCE::instance()->join("test");
	cout << "Node ID = " << D2MCE::instance()->nodeId() << endl;

	D2MCE::instance()->barrier(2);

	usleep(50);
	int a = 5;
	int b = a + 2;
	int c = b - a;
	SharedMemory *sm = D2MCE::instance()->createSharedMemory("mem", sizeof(int));
	cout << "Memory Address = " << hex << (unsigned)sm << endl;
	sm->lock();
	sm->load();
	cout << *((int *)sm->buffer()) << endl;
	sm->unlock();

	D2MCE::instance()->barrier(2);
	return 0;
}
