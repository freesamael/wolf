/**
 * \file CFlowVector.h
 * \date Jun 28, 2010
 * \author samael
 */

#ifndef CFLOWVECTOR_H_
#define CFLOWVECTOR_H_

#include <vector>
#include "IDrop.h"

namespace wolf
{

template <typename T>
class CFlowVector: public std::vector<T>, public IDrop
{
public:
	IDrop* clone() const { return new CFlowVector<T>(*this); }
};

}

#endif /* CFLOWVECTOR_H_ */
