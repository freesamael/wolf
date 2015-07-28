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
	explicit XTlvObject(XType e, uint32_t id = TLV_TYPE_INVALID,
			const std::string &name = "?") throw();
	virtual ~XTlvObject() throw() {}
	inline XType xtype() const throw() { return _e; }

private:
	XType _e;
};

}

#endif /* XTLVOBJECT_H_ */
