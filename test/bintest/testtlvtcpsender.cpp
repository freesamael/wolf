/**
 * \file testtlvtcpsender.cpp
 * \date Jul 15, 2010
 * \author samael
 */

#include <iostream>
#include <CTcpSocket.h>
#include <CTcpTlvWriter.h>
#include <CTime.h>
#include "testtlv.h"

using namespace std;
using namespace wolf;

int main(int argc, char *argv[])
{
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " <addr>" << endl;
		return EXIT_FAILURE;
	}

	CTcpSocket conn;
	conn.activeOpen(argv[1], 5566);

	CTcpTlvWriter writer(&conn);
	CTlvString str = generateString('A', 50000);

	CTime stime = CTime::now();
	unsigned times = 0;
	while ((CTime::now() - stime) < CTime(3, 0)) {
		writer.writeObject(str);
		times++;
	}

	cout << "Send " << times << " times." << endl;
	return 0;
}
