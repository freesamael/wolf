/**
 * \file ITlvBlock.cpp
 * \date Mar 30, 2010
 * \author samael
 */

#include "ITlvBlock.h"

namespace wolf
{

/// Size of type field.
const uint32_t ITlvBlock::szType = sizeof(uint32_t);
/// Size of length field.
const uint32_t ITlvBlock::szLength = sizeof(uint32_t);
/// Size of a header (type + length).
const uint32_t ITlvBlock::szHeader = sizeof(uint32_t) * 2;

}
