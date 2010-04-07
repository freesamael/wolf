/*
 * testtcpclient.cpp
 *
 *  Created on: Mar 30, 2010
 *      Author: samael
 */

#include <iostream>
#include <string>
#include "TCPSocket.h"
#include "TLVReaderWriter.h"
#include "TLVString.h"

using namespace std;
using namespace cml;

int main()
{
    string str;
    TCPSocket sock;
    TLVReaderWriter rw(&sock);
    sock.activeOpen("127.0.0.1", 5566);

    do {
        cin >> str;

        // Write out.
        TLVString ostr(str);
        rw.write(ostr);

        // Read in.
        ITLVObject *obj;
        TLVString *istr;
        obj = rw.read();
        if ((istr = dynamic_cast<TLVString *>(obj))) {
            cout << istr->toString() << endl;
        }
        delete obj;
    } while (str != "quit");

    return 0;
}
