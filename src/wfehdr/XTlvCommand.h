/*
 * XTlvCommand.h
 *
 *  Created on: Jul 15, 2010
 *      Author: samael
 */

#ifndef XTLVCOMMAND_H_
#define XTLVCOMMAND_H_

#include "AException.h"

namespace wfe
{

class XTlvCommand: public cml::AException
{
public:
	typedef enum XType {
		NOT_TLV_COMMAND
	} XType;
	static const char *XTypeString[];
	XTlvCommand(const std::string &func, int line, const std::string &type,
			XType e) throw();
	virtual ~XTlvCommand() throw() {}
	inline XType xtype() const throw() { return _e; }
	inline const char* what() const throw() { return _estr.c_str(); }
	inline std::string& toString() const throw() { return _estr; }

private:
	XType _e;
	std::string _estr;
};

}

#endif /* XTLVCOMMAND_H_ */
