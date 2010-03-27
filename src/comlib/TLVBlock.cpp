/*
 * TLVBlock.cpp
 *
 *  Created on: Mar 10, 2010
 *      Author: samael
 */

#include "TLVBlock.h"

namespace cml
{

/**
 * @note TLVBlock takes the ownership of value buffer, and deletes it on
 * destruction.
 */
TLVBlock::TLVBlock(unsigned short type, unsigned short length, char *value):
		_type(type), _length(length), _value(value)
{
}

TLVBlock::~TLVBlock()
{
	delete _value;
}

/**
 * @brief Allocate proper buffer according to length.
 * @note It will delete the old buffer if any. If it's not what you want,
 * call setValue(NULL) first.
 */
void TLVBlock::allocBuffer()
{
	 delete _value;
	 _value = new char[_length];
}

}
