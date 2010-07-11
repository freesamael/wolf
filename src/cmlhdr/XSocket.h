/**
 * \file XSocket.h
 * \date Jul 10, 2010
 * \author samael
 */

#ifndef XSOCKET_H_
#define XSOCKET_H_

#include <exception>
#include <string>

namespace cml
{

/**
 * Representing socket related exceptions.
 */
class XSocket: public std::exception
{
public:
	typedef enum ERR
	{
		ERRNO,
		INVALID_SOCKET_TYPE,
		INVALID_SOCKET_STATE,
		INVALID_TTL,
		UNKNOWN_ERR
	} ERR;
	explicit XSocket(int e) throw();
	explicit XSocket(ERR e) throw();
	virtual ~XSocket() throw() {}
	inline ERR errtype() const throw() { return _e; }
	inline int errnum() const throw() { return _eno; }
	inline const std::string& toString() const throw() { return _estr; }

private:
	ERR _e;
	int _eno;
	std::string _estr;
};

}

#endif /* XSOCKET_H_ */
