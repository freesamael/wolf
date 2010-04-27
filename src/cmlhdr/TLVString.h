/**
 * \file TLVString.h
 * \date Mar 10, 2010
 * \author samael
 */

#ifndef TLVSTRING_H_
#define TLVSTRING_H_

#include <string>
#include "ITLVObject.h"

namespace cml
{

/**
 * std::string wrapper to support TLV.
 */
class TLVString: public ITLVObject
{
public:
	TLVString(): _str() {}
	TLVString(const char *str): _str(str) {}
	TLVString(const std::string &str): _str(str) {}
	StandardTLVBlock* toTLVBlock() const;
	inline std::string toString() const { return _str; }
	void setString(const char *str) { _str = str; }
	void setString(const std::string &str) { _str = str; }

private:
	std::string _str;
};

}

#endif /* TLVSTRING_H_ */
