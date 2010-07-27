/**
 * \file AActor.cpp
 * \date Mar 28, 2010
 * \author samael
 */

#include "AActor.h"

using namespace std;

namespace wolf
{

const string AActor::StateString[] =
		{"Not Ready", "Ready", "Running", "Post Running", "Finished",
				"Terminated"};

IPort* AActor::addPort(IPort::Type type)
{
	if (type == IPort::SINK) {
		CSinkPort *p = new CSinkPort(this);
		_sinkp.push_back(p);
		return p;
	} else {
		CSourcePort *p = new CSourcePort(this);
		_srcp.push_back(p);
		return p;
	}
}

void AActor::removePort(IPort *port)
{
	if (port->type() == IPort::SINK) {
		// Delete a sink port.
		vector<CSinkPort *>::iterator iter;
		for (iter = _sinkp.begin(); iter != _sinkp.end(); ++iter) {
			if (*iter == port) {
				delete *iter;
				_sinkp.erase(iter);
				return;
			}
		}
	} else {
		// Delete a source port.
		vector<CSourcePort *>::iterator iter;
		for (iter = _srcp.begin(); iter != _srcp.end(); ++iter) {
			if (*iter == port) {
				delete *iter;
				_srcp.erase(iter);
				return;
			}
		}
	}
}

}
