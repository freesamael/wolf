/**
 * \file CTime.h
 * \date Jun 26, 2010
 * \author samael
 */

#ifndef CTIME_H_
#define CTIME_H_

#include <sys/time.h>
#include <cstddef>
#include <string>
#include <ostream>

namespace cml
{

class CTime
{
public:
	CTime(time_t sec = 0, suseconds_t usec = 0): _t()
		{ _t.tv_sec = sec; _t.tv_usec = usec; }
	CTime(const timeval &t): _t(t) {}
	CTime(const CTime &t): _t(t._t) {}
	time_t second() const { return _t.tv_sec; }
	void setSecond(time_t s) { _t.tv_sec = s; }
	suseconds_t microsecond() const { return _t.tv_usec; }
	void setMicrosecond(suseconds_t s) { _t.tv_usec = s; }
	CTime& operator=(const CTime &o) { _t = o._t; return *this; }
	CTime operator+(const CTime &o);
	CTime operator-(const CTime &o);
	CTime operator+=(const CTime &o) { *this = *this + o; return *this; }
	CTime operator-=(const CTime &o) { *this = *this - o; return *this; }
	bool operator>(const CTime &o) { return timercmp(&_t, &o._t, >); }
	bool operator<(const CTime &o) { return timercmp(&_t, &o._t, <); }
	bool operator!=(const CTime &o) { return timercmp(&_t, &o._t, !=); }
	bool operator==(const CTime &o) { return !timercmp(&_t, &o._t, !=); }
	bool operator>=(const CTime &o) { return !timercmp(&_t, &o._t, <); }
	bool operator<=(const CTime &o) { return !timercmp(&_t, &o._t, >); }
	std::string toString() const;

	static CTime now() { CTime t; gettimeofday(&(t._t), NULL); return t; }

private:
	timeval _t;
};

}

extern std::ostream& operator<<(std::ostream &o, const cml::CTime &t);

#endif /* CTIME_H_ */
