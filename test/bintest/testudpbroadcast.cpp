/**
 * \file testudpbroadcast.cpp
 * \date Mar 31, 2010
 * \author samael
 */

#include <CUdpSocket.h>
#include <CTlvReaderWriter.h>
#include <CTlvString.h>

using namespace cml;

int main()
{
	CUdpSocket sock;
	CTlvString str("i wanna go home...");
	CTlvReaderWriter rw;

	sock.setBroadcast(true);
	sock.setTTL(1);
	for (int i = 0; i < 10; i++) {
		rw.sendto(str, "255.255.255.255", 5566, &sock);
		sleep(1);
	}

	return 0;
}
