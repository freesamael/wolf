/**
 * \file ACommandListener.cpp
 * \date Jun 14, 2010
 * \author samael
 */

#include <string>
#include <typeinfo>
#include "CTcpTlvReader.h"
#include "ITlvObject.h"
#include "ACommandListener.h"
#include "XTlvCommand.h"

using namespace std;
using namespace cml;

namespace wfe
{

void wfe::ACommandListener::run()
{
	CTcpTlvReader reader(_sock);

	while (!isDone()) {
		ITlvObject *inobj;
		if (!(inobj = reader.readObject()))
			break; // End of file.
		CTlvCommand *incmd;
		if (!(incmd = dynamic_cast<CTlvCommand *>(inobj))) {
			string type = typeid(inobj).name();
			delete inobj;
			throw XTlvCommand(__PRETTY_FUNCTION__, __LINE__,
					XTlvCommand::INVALID_OBJECT, typeid(inobj).name());
		} else {
			try {
				process(incmd);
			} catch (const XTlvCommand &x) {
				delete incmd;
				throw x;
			}
			delete incmd;
		}
	}
}

}
