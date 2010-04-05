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
	virtual unsigned short size() const = 0; ///< Total size (header + value).
	virtual const char* getCompleteBuffer() const = 0;
	virtual const char* getValueBuffer() const = 0;
};

}

#endif /* ITLVBLOCK_H_ */
