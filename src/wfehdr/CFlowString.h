/**
 * \file CFlowString.h
 * \date Jun 20, 2010
 * \author samael
 */

#ifndef CFLOWSTRING_H_
#define CFLOWSTRING_H_

#include "IDrop.h"
#include "CTlvString.h"

namespace wolf
{

/**
 * Specialized CTlvString implementing IDrop.
 */
class CFlowString: public IDrop, public wolf::CTlvString
{
public:
	CFlowString() {}
	CFlowString(const char *str): CTlvString(str) {}
	CFlowString(const std::string &str): CTlvString(str) {}
	CFlowString(const wolf::CTlvString &o): CTlvString(o) {}
	wolf::CTlvBlock* toTLVBlock() const;
	IDrop* clone() const;
};

}

#endif /* CFLOWSTRING_H_ */
