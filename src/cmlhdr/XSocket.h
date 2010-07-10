/**
 * \file XSocket.h
 * \date Jul 10, 2010
 * \author samael
 */

#ifndef XSOCKET_H_
#define XSOCKET_H_

#include <exception>

namespace cml
{

/**
 * Representing socket related exceptions.
 */
class XSocket: public std::exception
{
public:
	XSocket() throw();
	virtual ~XSocket() throw();
};

}

#endif /* XSOCKET_H_ */
