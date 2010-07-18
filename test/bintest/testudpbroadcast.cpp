/**
 * \file testudpbroadcast.cpp
 * \date Mar 31, 2010
 * \author samael
 */

#include <CUdpSocket.h>
#include <CUdpTlvWriter.h>
#include <CTlvString.h>

using namespace cml;

int main()
{
	CUdpSocket sock;
	CTlvString str("i wanna go home...");
	CUdpTlvWriter writer(&sock);

	sock.setBroadcast(true);
	for (int i = 0; i < 10; i++) {
		writer.sendObjectTo(str, "255.255.255.255", 5566);
		sleep(1);
	}

	return 0;
}
