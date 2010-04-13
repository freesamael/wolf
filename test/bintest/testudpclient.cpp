/**
 * \file udpclient.cpp
 * \date Mar 30, 2010
 * \author samael
 */

#include <iostream>
#include <string>
#include "UDPSocket.h"
#include "TLVReaderWriter.h"
#include "TLVString.h"
#include "HostAddress.h"

using namespace std;
using namespace cml;

int main()
{
    string str;
    UDPSocket sock;
    TLVReaderWriter rw(&sock);
    HostAddress addr;
    unsigned short port;

    do {
    	cin >> str;

        // Write out.
        TLVString ostr(str);
        rw.sendto(ostr, "127.0.0.1", 5566);

        // Read in.
        ITLVObject *obj;
        TLVString *istr;
        obj = rw.recvfrom(&addr, &port);
        if ((istr = dynamic_cast<TLVString *>(obj))) {
            cout << istr->toString() << endl;
        }
        delete obj;
    } while (str != "quit");

    return 0;
}
