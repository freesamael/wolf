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
		UNKNOWN_ERR
	} XType;
	static const char *XTypeString[];
	explicit XSocket(const char *func, int line, int e) throw();
	explicit XSocket(const char *func, int line, XType e) throw();
	virtual ~XSocket() throw() {}
	inline XType xtype() const throw() { return _e; }
	inline int errnum() const throw() { return _eno; }
	inline const char* what() const throw() { return _estr.c_str(); }
	inline std::string toString() const throw() { return _estr; }

private:
	XType _e;
	int _eno;
	std::string _estr;
};

}

#endif /* XSOCKET_H_ */
