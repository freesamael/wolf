/**
 * \file udpserver.cpp
 * \date Mar 30, 2010
 * \author samael
 */

#include <iostream>
#include <string>
#include "ASocket.h"
#include "CUdpSocket.h"
#include "CTlvReaderWriter.h"
#include "CTlvString.h"
#include "CHostAddress.h"

using namespace std;
using namespace cml;

int main()
{
	CUdpSocket sock;
	CTlvReaderWriter rw(&sock);
    ITlvObject *obj;
    CTlvString *instr;
    string str;
    CHostAddress addr;
    unsigned short port;

    sock.passiveOpen(5566);
    do {
    	obj = rw.recvfrom(&addr, &port);
    	if ((instr = dynamic_cast<CTlvString *>(obj))) {
    		str = instr->toString();
    		cout << str << endl;
    		rw.sendto(*instr, addr, port);
    	}
    	delete obj;
    } while (str != "quit");

    return 0;
}
