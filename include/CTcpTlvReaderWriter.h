/*
 * CTcpTlvReaderWriter.h
 *
 *  Created on: Jul 15, 2010
 *      Author: samael
 */

#ifndef CTCPTLVREADERWRITER_H_
#define CTCPTLVREADERWRITER_H_

#include "CTcpTlvReader.h"
#include "CTcpTlvWriter.h"

namespace wolf {

class CTcpTlvReaderWriter: public CTcpTlvReader, public CTcpTlvWriter {
public:
	CTcpTlvReaderWriter(CTcpSocket *sock): CTcpTlvReader(sock),
			CTcpTlvWriter(sock) {}
	~CTcpTlvReaderWriter() {}
};

}

#endif /* CTCPTLVREADERWRITER_H_ */
