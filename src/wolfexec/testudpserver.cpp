/*
 * udpserver.cpp
 *
 *  Created on: Mar 30, 2010
 *      Author: samael
 */

#include <iostream>
#include <string>
#include "UDPSocket.h"
#include "TLVReaderWriter.h"
#include "TLVString.h"

using namespace std;
using namespace cml;

int main()
{
//    TCPServer server;
//    server.listen(5566, 10);
//
//    TCPSocket *sock;
//    while ((sock = server.accept())) {
//        // Read in.
//        while (true) {
//            TLVReaderWriter rw(sock);
//            ITLVObject *obj = rw.read();
//            TLVString *str;
//            if ((str = dynamic_cast<TLVString *>(obj))) {
//                cout << str->toString() << endl;
//                rw.write(*str);
//            }
//            delete obj;
//        }
//    }

    return 0;
}
