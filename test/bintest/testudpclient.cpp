/**
 * \file udpclient.cpp
 * \date Mar 30, 2010
 * \author samael
 */

#include <iostream>
#include <string>
#include "CUdpSocket.h"
#include "CTlvString.h"
#include "CHostAddress.h"
#include "CUdpTlvReaderWriter.h"

using namespace std;
using namespace wolf;

int main()
{
    string str;
    CUdpSocket sock;
    CUdpTlvReaderWriter rw(&sock);
    CHostAddress addr;
    unsigned short port;

    do {
    	cin >> str;

        // Write out.
        CTlvString ostr(str);
        rw.sendObjectTo(ostr, "127.0.0.1", 5566);

        // Read in.
        ITlvObject *obj;
        CTlvString *istr;
        obj = rw.recvObjectFrom(&addr, &port);
        if ((istr = dynamic_cast<CTlvString *>(obj))) {
            cout << istr->toString() << endl;
        }
        delete obj;
    } while (str != "quit");

    return 0;
}
