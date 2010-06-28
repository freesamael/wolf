/**
 * \file DVector.h
 * \date Jun 28, 2010
 * \author samael
 */

#ifndef DVECTOR_H_
#define DVECTOR_H_

#include <vector>
#include "IDrop.h"

namespace wfe
{

template <typename T>
class DVector: public std::vector<T>, public IDrop
{
public:
	IDrop* clone() const { return new DVector<T>(*this); }
};

}

#endif /* DVECTOR_H_ */
