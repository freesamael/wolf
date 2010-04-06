/*
 * testtcpserver.cpp
 *
 *  Created on: Mar 30, 2010
 *      Author: samael
 */

#include <iostream>
#include <string>
#include <TCPSocket.h>
#include "TLVReaderWriter.h"
#include "TLVString.h"

using namespace std;
using namespace cml;

int main()
{
    TCPSocket msock;
    msock.passiveOpen(5566);
    TCPSocket *ssock = msock.accept();
    TLVReaderWriter rw(ssock);
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
