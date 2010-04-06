/*
 * TLVString.h
 *
 *  Created on: Mar 10, 2010
 *      Author: samael
 */

#ifndef TLVSTRING_H_
#define TLVSTRING_H_

#include <string>
#include "ITLVObject.h"

namespace cml
{

class TLVString: public ITLVObject
{
public:
	TLVString() {}
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