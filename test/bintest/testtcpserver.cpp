/**
 * \file testtcpserver.cpp
 * \date Mar 30, 2010
 * \author samael
 */

#include <iostream>
#include <string>
#include <CTcpSocket.h>
#include "CTlvReaderWriter.h"
#include "CTlvString.h"

using namespace std;
using namespace cml;

int main()
{
    CTcpSocket msock;
    msock.passiveOpen(5566);
    CTcpSocket *ssock = msock.accept();
    CTlvReaderWriter rw(ssock);
    ITlvObject *obj;
    cout << "local address: " << msock.currentAddress().toString() << endl;
    cout << "local address: " << ssock->currentAddress().toString() << endl;

	// Read in.
	while ((obj = rw.read())) {
		CTlvString *str;
		if ((str = dynamic_cast<CTlvString *>(obj))) {
			cout << str->toString() << endl;
			rw.write(*str);
		}
		delete obj;
	}

    return 0;
}
