/**
 * \file udpserver.cpp
 * \date Mar 30, 2010
 * \author samael
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
    TLVString *instr;
    string str;
    HostAddress addr;
    unsigned short port;

    sock.passiveOpen(5566);
    do {
    	obj = rw.recvfrom(&addr, &port);
    	if ((instr = dynamic_cast<TLVString *>(obj))) {
    		str = instr->toString();
    		cout << str << endl;
    		rw.sendto(*instr, addr, port);
    	}
    	delete obj;
    } while (str != "quit");

    return 0;
}
