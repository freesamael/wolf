/*
 * ITLVBlock.cpp
 *
 *  Created on: Mar 30, 2010
 *      Author: samael
 */

#include "ITLVBlock.h"

namespace cml
{

/// Size of type field.
const unsigned short ITLVBlock::szType = sizeof(unsigned short);
/// Size of length field.
const unsigned short ITLVBlock::szLength = sizeof(unsigned short);
/// Size of a header (type + length).
const unsigned short ITLVBlock::szHeader = sizeof(unsigned short) * 2;

}
