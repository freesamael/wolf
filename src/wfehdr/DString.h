/**
 * \file DString.h
 * \date Jun 20, 2010
 * \author samael
 */

#ifndef DSTRING_H_
#define DSTRING_H_

#include "IDrop.h"
#include "TLVString.h"

namespace wfe
{

/**
 * Specialized TLVString implementing IDrop.
 */
class DString: public IDrop, public cml::TLVString
{
public:
	DString() {}
	DString(const char *str): TLVString(str) {}
	DString(const std::string &str): TLVString(str) {}
	DString(const cml::TLVString &o): TLVString(o) {}
	cml::StandardTLVBlock* toTLVBlock() const;
	IDrop* clone() const;
};

}

#endif /* DSTRING_H_ */
