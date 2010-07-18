/**
 * \file CUdpTlvReaderWriter.h
 * \date Jul 18, 2010
 * \author samael
 */

#ifndef CUDPTLVREADERWRITER_H_
#define CUDPTLVREADERWRITER_H_

#include "CUdpTlvReader.h"
#include "CUdpTlvWriter.h"

namespace cml
{

class CUdpTlvReaderWriter: public CUdpTlvReader, public CUdpTlvWriter
{
public:
	CUdpTlvReaderWriter(CUdpSocket *sock): CUdpTlvReader(sock),
			CUdpTlvWriter(sock) {}
	~CUdpTlvReaderWriter() {}
};

}

#endif /* CUDPTLVREADERWRITER_H_ */
