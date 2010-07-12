/**
 * \file CTcpDataReader.h
 * \date Jul 12, 2010
 * \author samael
 */

#ifndef CTCPDATAREADER_H_
#define CTCPDATAREADER_H_

#include "IRunnable.h"

namespace cml
{

class CTcpDataReader: public IRunnable
{
public:
	CTcpDataReader();
	~CTcpDataReader();
};

}

#endif /* CTCPDATAREADER_H_ */
