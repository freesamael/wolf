/**
 * \file XTlvObject.h
 * \date Jul 14, 2010
 * \author samael
 */

#ifndef XTLVOBJECT_H_
#define XTLVOBJECT_H_

#include <inttypes.h>
#include "XWolf.h"
#include "CmlTLVTypes.h"

namespace wolf
{

/**
 * Exceptions of TLV objects and blocks.
 */
class XTlvObject: public XWolf
{
public:
	typedef enum XType {
		INVALID_TYPE_ID,
		NO_SUITABLE_CREATOR,
		NULL_BLOCK_GENERATED,
		BLOCK_TOO_SHORT
	} XType;
	static const char *XTypeString[];
	explicit XTlvObject(const std::string &func, int line, XType e,
			uint16_t id = TLV_TYPE_INVALID, const std::string &name = "?")
			throw();
	virtual ~XTlvObject() throw() {}
	inline XType xtype() const throw() { return _e; }
	inline const char* what() const throw() { return _estr.c_str(); }
	inline std::string toString() const throw() { return _estr; }

private:
	XType _e;
	std::string _estr;
};

}

#endif /* XTLVOBJECT_H_ */
