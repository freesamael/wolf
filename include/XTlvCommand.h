/*
 * XTlvCommand.h
 *
 *  Created on: Jul 15, 2010
 *      Author: samael
 */

#ifndef XTLVCOMMAND_H_
#define XTLVCOMMAND_H_

#include "XWolf.h"
#include "CTlvCommand.h"

namespace wolf
{

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
	XTlvCommand(const std::string &func, int line, XType e,
			const std::string &type) throw();
	XTlvCommand(const std::string &func, int line, XType e,
			const CTlvCommand &cmd) throw();
	virtual ~XTlvCommand() throw() {}
	inline XType xtype() const throw() { return _e; }
	inline const char* what() const throw() { return _estr.c_str(); }
	inline std::string toString() const throw() { return _estr; }

private:
	XType _e;
	std::string _estr;
};

}

#endif /* XTLVCOMMAND_H_ */
