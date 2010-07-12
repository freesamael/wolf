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
	typedef enum XType
	{
		ERRNO,
		INVALID_SOCKET_TYPE,
		INVALID_SOCKET_STATE,
		INVALID_TTL,
		UNKNOWN_ERR
	} XType;
	explicit XSocket(int e) throw();
	explicit XSocket(XType e) throw();
	virtual ~XSocket() throw() {}
	inline XType xtype() const throw() { return _e; }
	inline int errnum() const throw() { return _eno; }
	inline const std::string& toString() const throw() { return _estr; }

private:
	XType _e;
	int _eno;
	std::string _estr;
};

}

#endif /* XSOCKET_H_ */
