/**
 * \file CSourcePort.cpp
 * \date Apr 12, 2010
 * \author samael
 */

#include "CSourcePort.h"

#include <iostream>
#include <sstream>
#include "HelperMacros.h"
#include "CChannel.h"

namespace wolf
{

/**
 * Write an item to the channel attached on this port.
 */
void CSourcePort::writeChannel(IDrop *item)
{
	if (_channel) {
		_channel->write(item);
	} else {
		PERR("No channel attached.");
	}
}

}
