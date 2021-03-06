/**
 * \file CChannel.h
 * \date Mar 22, 2010
 * \author samael
 */

#ifndef CCHANNEL_H_
#define CCHANNEL_H_

#include <string>
#include <vector>
#include "CMutex.h"
#include "IDrop.h"

namespace wolf
{

class CSinkPort;

/**
 * Used to connect ports. A channel can have one writer and multiple readers.
 */
class CChannel
{
public:
	CChannel(): _mutex(), _readers() { }
	~CChannel() { }
	inline const std::vector<CSinkPort *>& readers() { return _readers; }
	void attachReader(CSinkPort *port);
	void detachReader(CSinkPort *port);
	void write(IDrop *item);

private:
	CMutex _mutex;
	std::vector<CSinkPort *> _readers;
};

}

#endif /* CCHANNEL_H_ */
