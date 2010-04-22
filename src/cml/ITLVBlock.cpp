/**
 * \file ITLVBlock.cpp
 * \date Mar 30, 2010
 * \author samael
 */

#include "ITLVBlock.h"

namespace cml
{

/// Size of type field.
const uint16_t ITLVBlock::szType = sizeof(uint16_t);
/// Size of length field.
const uint16_t ITLVBlock::szLength = sizeof(uint16_t);
/// Size of a header (type + length).
const uint16_t ITLVBlock::szHeader = sizeof(uint16_t) * 2;

}
