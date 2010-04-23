/**
 * \file SourcePort.cpp
 * \date Apr 12, 2010
 * \author samael
 */

#include <iostream>
#include <HelperMacros.h>
#include "SourcePort.h"
#include "Channel.h"

namespace wfe
{

/**
 * Write an item to the channel attached on this port.
 */
void SourcePort::writeChannel(IDrop *item)
{
	if (_channel) {
		_channel->write(item);
	} else {
		PERR("No channel attached.");
	}
}

}
