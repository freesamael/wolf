/*
 * testudpbroadcast.cpp
 *
 *  Created on: Mar 31, 2010
 *      Author: samael
 */

#include <UDPSocket.h>
#include <TLVReaderWriter.h>
#include <TLVString.h>

using namespace cml;

int main()
{
	UDPSocket sock;
	TLVString str("i wanna go home...");
	TLVReaderWriter rw;

	sock.open();
	sock.setBroadcast(true);
	sock.setTTL(1);
	for (int i = 0; i < 10; i++) {
		rw.sendto(str, "255.255.255.255", 5566, &sock);
		sleep(1);
	}

	return 0;
}
