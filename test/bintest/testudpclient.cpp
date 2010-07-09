/**
 * \file udpclient.cpp
 * \date Mar 30, 2010
 * \author samael
 */

#include <iostream>
#include <string>
#include "CUdpSocket.h"
#include "CTlvReaderWriter.h"
#include "CTlvString.h"
#include "CHostAddress.h"

using namespace std;
using namespace cml;

int main()
{
    string str;
    CUdpSocket sock;
    CTlvReaderWriter rw(&sock);
    CHostAddress addr;
    unsigned short port;

    do {
    	cin >> str;

        // Write out.
        CTlvString ostr(str);
        rw.sendto(ostr, "127.0.0.1", 5566);

        // Read in.
        ITlvObject *obj;
        CTlvString *istr;
        obj = rw.recvfrom(&addr, &port);
        if ((istr = dynamic_cast<CTlvString *>(obj))) {
            cout << istr->toString() << endl;
        }
        delete obj;
    } while (str != "quit");

    return 0;
}
