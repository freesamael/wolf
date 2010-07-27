/**
 * \file testtlvtcpreceiver.cpp
 * \date Jul 15, 2010
 * \author samael
 */

#include <iostream>
#include <cassert>
#include <CTcpServer.h>
#include <CTcpTlvReader.h>
#include "testtlv.h"

using namespace wolf;
using namespace std;

int main()
{
	CTcpServer server;
	server.passiveOpen(5566, 10, true);
	CTcpSocket *conn = server.accept();
	CTcpTlvReader reader(conn);

	unsigned times = 0;

	CTlvString str = generateString('A', 50000);
	ITlvBlock *blk = str.toTLVBlock();
	unsigned size = blk->plainSize();
	delete blk;

	ITlvObject *obj;
	while ((obj = reader.readObject())) {
		CTlvString *instr = dynamic_cast<CTlvString *>(obj);
		assert((str.toString() == instr->toString()));
		delete instr;
		times++;
	}

	cout << "Got " << times << " times, " << (double)(size * times) / 1048576 << " MB." << endl;
	return 0;
}
