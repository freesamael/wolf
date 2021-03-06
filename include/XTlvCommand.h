/**
 * \file XTlvCommand.h
 * \date Jul 15, 2010
 * \author samael
 */

#ifndef XTLVCOMMAND_H_
#define XTLVCOMMAND_H_

#include "XWolf.h"
#include "CTlvCommand.h"

namespace wolf
{

/**
 * CTlvCommnad related exceptions.
 */
class XTlvCommand: public XWolf
{
public:
	typedef enum XType {
		INVALID_OBJECT,
		UNEXPECTED_COMMAND,
		INVALID_PARAM_NUM,
		INVALID_PARAM
	} XType;
	static const char *XTypeString[];
	XTlvCommand(XType e, const std::string &type) throw();
	XTlvCommand(XType e, const CTlvCommand &cmd) throw();
	virtual ~XTlvCommand() throw() {}
	inline XType xtype() const throw() { return _e; }

private:
	XType _e;
};

}

#endif /* XTLVCOMMAND_H_ */
