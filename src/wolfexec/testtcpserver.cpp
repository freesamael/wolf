/*
 * testtcpserver.cpp
 *
 *  Created on: Mar 30, 2010
 *      Author: samael
 */

#include <iostream>
#include <string>
#include "TCPServer.h"
#include "TLVReaderWriter.h"
#include "TLVString.h"

using namespace std;
using namespace cml;

int main()
{
    TCPServer server;
    server.listen(5566, 10);
    TCPSocket *sock = server.accept();
    TLVReaderWriter rw(sock);
    ITLVObject *obj;

	// Read in.
	while ((obj = rw.read())) {
		TLVString *str;
		if ((str = dynamic_cast<TLVString *>(obj))) {
			cout << str->toString() << endl;
			rw.write(*str);
		}
		delete obj;
	}

    return 0;
}
