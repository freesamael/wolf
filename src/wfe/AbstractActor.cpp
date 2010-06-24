/**
 * \file AbstractActor.cpp
 * \date Mar 28, 2010
 * \author samael
 */

#include "AbstractActor.h"

using namespace std;

namespace wfe
{

const string AbstractActor::StateString[] =
		{"Not Ready", "Ready", "Running", "Post Running", "Finished",
				"Terminated"};

IPort* AbstractActor::addPort(IPort::Type type)
{
	if (type == IPort::SINK) {
		SinkPort *p = new SinkPort(this);
		_sinkp.push_back(p);
		return p;
	} else {
		SourcePort *p = new SourcePort(this);
		_srcp.push_back(p);
		return p;
	}
}

void AbstractActor::removePort(IPort *port)
{
	if (port->type() == IPort::SINK) {
		// Delete a sink port.
		vector<SinkPort *>::iterator iter;
		for (iter = _sinkp.begin(); iter != _sinkp.end(); ++iter) {
			if (*iter == port) {
				delete *iter;
				_sinkp.erase(iter);
				return;
			}
		}
	} else {
		// Delete a source port.
		vector<SourcePort *>::iterator iter;
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
