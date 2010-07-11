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
	typedef enum ERR {
		ERRNO,
		THREAD_ALREADY_STARTED,
		UNKNOWN
	} ERR;
	explicit XThread(int e) throw();
	explicit XThread(ERR e) throw();
	virtual ~XThread() throw() {}

private:
	ERR _e;
	int _eno;
	std::string _estr;
};

}

#endif /* XTHREAD_H_ */
