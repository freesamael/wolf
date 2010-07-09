/**
 * \file testtcpclient.cpp
 * \date Mar 30, 2010
 * \author samael
 */

#include <iostream>
#include <string>
#include "CTcpSocket.h"
#include "CTlvReaderWriter.h"
#include "CTlvString.h"

using namespace std;
using namespace cml;

int main()
{
    string str;
    CTcpSocket sock;
    CTlvReaderWriter rw(&sock);
    sock.activeOpen("127.0.0.1", 5566);
    cout << "local address: " << sock.currentAddress().toString() << endl;

    do {
        cin >> str;

        // Write out.
        CTlvString ostr(str);
        rw.write(ostr);

        // Read in.
        ITlvObject *obj;
        CTlvString *istr;
        obj = rw.read();
        if ((istr = dynamic_cast<CTlvString *>(obj))) {
            cout << istr->toString() << endl;
        }
        delete obj;
    } while (str != "quit");

    return 0;
}
