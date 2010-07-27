/**
 * \file ITlvBlock.cpp
 * \date Mar 30, 2010
 * \author samael
 */

#include "ITlvBlock.h"

namespace wolf
{

/// Size of type field.
const uint16_t ITlvBlock::szType = sizeof(uint16_t);
/// Size of length field.
const uint16_t ITlvBlock::szLength = sizeof(uint16_t);
/// Size of a header (type + length).
const uint16_t ITlvBlock::szHeader = sizeof(uint16_t) * 2;

}
