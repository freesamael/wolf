/*
 * ITLVBlock.h
 *
 *  Created on: Mar 30, 2010
 *      Author: samael
 */

#ifndef ITLVBLOCK_H_
#define ITLVBLOCK_H_

namespace cml
{

/**
 * \interface ITLVBlock
 */
class ITLVBlock
{
public:
	static const unsigned short szType, szLength, szHeader;

	virtual ~ITLVBlock() {}
	virtual unsigned short type() const = 0;
	virtual unsigned short length() const = 0;
	virtual unsigned short plainSize() const = 0; ///< Total size (header + value).
	virtual const char* plainBuffer() const = 0;
	virtual const char* value() const = 0;
};

}

#endif /* ITLVBLOCK_H_ */
