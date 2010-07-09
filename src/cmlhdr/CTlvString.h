/**
 * \file CTlvString.h
 * \date Mar 10, 2010
 * \author samael
 */

#ifndef CTLVSTRING_H_
#define CTLVSTRING_H_

#include <string>
#include "ITlvObject.h"

namespace cml
{

/**
 * std::string wrapper to support TLV.
 */
class CTlvString: public ITlvObject
{
public:
	CTlvString(): _str() {}
	CTlvString(const char *str): _str(str) {}
	CTlvString(const std::string &str): _str(str) {}
	CTlvString(const CTlvString &o): ITlvObject(), _str(o._str) {}
	CTlvBlock* toTLVBlock() const;
	inline std::string toString() const { return _str; }
	void setString(const char *str) { _str = str; }
	void setString(const std::string &str) { _str = str; }

private:
	std::string _str;
};

}

#endif /* CTLVSTRING_H_ */
