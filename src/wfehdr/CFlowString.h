/**
 * \file CFlowString.h
 * \date Jun 20, 2010
 * \author samael
 */

#ifndef CFLOWSTRING_H_
#define CFLOWSTRING_H_

#include "IDrop.h"
#include "CTlvString.h"

namespace wfe
{

/**
 * Specialized CTlvString implementing IDrop.
 */
class CFlowString: public IDrop, public cml::CTlvString
{
public:
	CFlowString() {}
	CFlowString(const char *str): CTlvString(str) {}
	CFlowString(const std::string &str): CTlvString(str) {}
	CFlowString(const cml::CTlvString &o): CTlvString(o) {}
	cml::CTlvBlock* toTLVBlock() const;
	IDrop* clone() const;
};

}

#endif /* CFLOWSTRING_H_ */
