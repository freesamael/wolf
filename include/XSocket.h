/**
 * \file XSocket.h
 * \date Jul 10, 2010
 * \author samael
 */

#ifndef XSOCKET_H_
#define XSOCKET_H_

#include "XWolf.h"

namespace wolf
{

/**
 * Representing socket related exceptions.
 */
class XSocket: public XWolf
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
	explicit XSocket(int e) throw();
	explicit XSocket(XType e) throw();
	virtual ~XSocket() throw() {}
	inline XType xtype() const throw() { return _e; }
	inline int errnum() const throw() { return _eno; }

private:
	XType _e;
	int _eno;
};

}

#endif /* XSOCKET_H_ */
