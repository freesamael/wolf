/*
 * TLVReaderWriter.h
 *
 *  Created on: Mar 11, 2010
 *      Author: samael
 */

#ifndef TLVREADERWRITER_H_
#define TLVREADERWRITER_H_

#include "AbstractSocket.h"

namespace cml
{

class UDPSocket;
class TLVReaderWriter
{
public:
	TLVReaderWriter(AbstractSocket *socket = NULL);
	~TLVReaderWriter();
	ITLVObject* read(AbstractSocket *socket = NULL);
	ITLVObject* recvfrom(HostAddress *addr, unsigned short *port,
			UDPSocket *socket = NULL);
	bool write(const ITLVObject &obj, AbstractSocket *socket = NULL);
	bool sendto(const ITLVObject &obj, const HostAddress &addr,
			unsigned short port, UDPSocket *socket = NULL);

private:
	AbstractSocket *_socket;
};

}

#endif /* TLVREADERWRITER_H_ */
