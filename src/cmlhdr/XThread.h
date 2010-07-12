/**
 * \file XThread.h
 * \date Jul 11, 2010
 * \author samael
 */

#ifndef XTHREAD_H_
#define XTHREAD_H_

#include <exception>
#include <string>

namespace cml
{

/**
 * Representing thread related exceptions.
 */
class XThread: public std::exception
{
public:
	typedef enum XType {
		ERRNO,
		THREAD_ALREADY_STARTED,
		UNKNOWN
	} XType;
	explicit XThread(int e) throw();
	explicit XThread(XType e) throw();
	virtual ~XThread() throw() {}
	inline XType xtype() const throw() { return _e; }
	inline int errnum() const throw() { return _eno; }
	inline const std::string& toString() const { return _estr; }

private:
	XType _e;
	int _eno;
	std::string _estr;
};

}

#endif /* XTHREAD_H_ */
