/**
 * \file udpserver.cpp
 * \date Mar 30, 2010
 * \author samael
 */

#include <iostream>
#include <string>
#include "ASocket.h"
#include "CUdpSocket.h"
#include "CUdpTlvReaderWriter.h"
#include "CTlvString.h"
#include "CHostAddress.h"

using namespace std;
using namespace wolf;

int main()
{
	CUdpSocket sock;
	CUdpTlvReaderWriter rw(&sock);
    ITlvObject *obj;
    CTlvString *instr;
    string str;
    CHostAddress addr;
    unsigned short port;

    sock.passiveOpen(5566);
    do {
    	obj = rw.recvObjectFrom(&addr, &port);
    	if ((instr = dynamic_cast<CTlvString *>(obj))) {
    		str = instr->toString();
    		cout << str << endl;
    		rw.sendObjectTo(*instr, addr, port);
    	}
    	delete obj;
    } while (str != "quit");

    return 0;
}
