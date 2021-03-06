/**
 * \file ITlvBlock.h
 * \date Mar 30, 2010
 * \author samael
 */

#ifndef ITLVBLOCK_H_
#define ITLVBLOCK_H_

#include <stdint.h>

namespace wolf
{

/**
 * \interface ITlvBlock
 *
 * ITLVBlock defines the interface of Type-Length-Value (TLV) block. This system
 * uses a TLV format with 16 bits type field and 16 bits length field.
 */
class ITlvBlock
{
public:
	static const uint32_t szType, szLength, szHeader;

	virtual ~ITlvBlock() {}
	virtual uint32_t type() const = 0;
	virtual uint32_t length() const = 0;
	virtual uint32_t plainSize() const = 0; ///< Size of plain buffer.
	virtual const char* plainBuffer() const = 0; ///< Plain buffer including header.
	virtual const char* value() const = 0;
};

}

#endif /* ITLVBLOCK_H_ */
