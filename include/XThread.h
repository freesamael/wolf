/**
 * \file XThread.h
 * \date Jul 11, 2010
 * \author samael
 */

#ifndef XTHREAD_H_
#define XTHREAD_H_

#include "XWolf.h"

namespace wolf
{

/**
 * Representing thread related exceptions.
 */
class XThread: public XWolf
{
public:
	typedef enum XType {
		ERRNO,
		THREAD_ALREADY_STARTED,
		UNKNOWN
	} XType;
	static const char *XTypeString[];
	explicit XThread(const std::string &func, int line, int e) throw();
	explicit XThread(const std::string &func, int line, XType e) throw();
	virtual ~XThread() throw() {}
	inline XType xtype() const throw() { return _e; }
	inline int errnum() const throw() { return _eno; }

private:
	XType _e;
	int _eno;
};

}

#endif /* XTHREAD_H_ */
