/*
 * udpserver.cpp
 *
 *  Created on: Mar 30, 2010
 *      Author: samael
 */

#include <iostream>
#include <string>
#include "AbstractSocket.h"
#include "UDPSocket.h"
#include "TLVReaderWriter.h"
#include "TLVString.h"
#include "HostAddress.h"

using namespace std;
using namespace cml;

int main()
{
	UDPSocket sock;
	TLVReaderWriter rw(&sock);
    ITLVObject *obj;
    HostAddress addr;
    unsigned short port;

    sock.passiveOpen(5566);
    while ((obj = rw.recvfrom(&addr, &port))) {
    	TLVString *str;
    	if ((str = dynamic_cast<TLVString *>(obj))) {
    		cout << str->toString() << endl;
    		rw.sendto(*str, addr, port);
    	}
    	delete obj;
    }

    return 0;
}
