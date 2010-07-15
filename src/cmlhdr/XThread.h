/**
 * \file XThread.h
 * \date Jul 11, 2010
 * \author samael
 */

#ifndef XTHREAD_H_
#define XTHREAD_H_

#include "AException.h"

namespace cml
{

/**
 * Representing thread related exceptions.
 */
class XThread: public AException
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
	inline const char* what() const throw() { return _estr.c_str(); }
	inline std::string toString() const throw() { return _estr; }

private:
	XType _e;
	int _eno;
	std::string _estr;
};

}

#endif /* XTHREAD_H_ */
