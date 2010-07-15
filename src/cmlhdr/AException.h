/**
 * \file AException.h
 * \date Jul 15, 2010
 * \author samael
 */

#ifndef AEXCEPTION_H_
#define AEXCEPTION_H_

#include <exception>
#include <string>

namespace cml
{

/**
 * Abstract class of all exceptions.
 */
class AException: public std::exception
{
public:
	virtual ~AException() throw() {}
	virtual std::string toString() const throw() = 0;
};

}

#endif /* AEXCEPTION_H_ */
