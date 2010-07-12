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

/// As timercmp is not in POSIX but BSD extension, we include the eglibc
/// implementation to make it compilable on POSIX systems without BSD-ext.
#ifndef timercmp
#define timercmp(a, b, CMP)                                                    \
	(((a)->tv_sec == (b)->tv_sec) ?                                            \
			((a)->tv_usec CMP (b)->tv_usec) :                                  \
			((a)->tv_sec CMP (b)->tv_sec))
#endif /* timercmp */

/// As timeradd is not in POSIX but BSD extension, we include the eglibc
/// implementation to make it compilable on POSIX systems without BSD-ext.
#ifndef timeradd
#define timeradd(a, b, result)                                                 \
	do {                                                                       \
		(result)->tv_sec = (a)->tv_sec + (b)->tv_sec;                          \
		(result)->tv_usec = (a)->tv_usec + (b)->tv_usec;                       \
		if ((result)->tv_usec >= 1000000L)                                     \
		{                                                                      \
			++(result)->tv_sec;                                                \
			(result)->tv_usec -= 1000000L;                                     \
		}                                                                      \
	} while (0)
#endif /* timeradd */

/// As timersub is not in POSIX but BSD extension, we include the eglibc
/// implementation to make it compilable on POSIX systems without BSD-ext.
#ifndef timersub
# define timersub(a, b, result)                                                \
	do {                                                                       \
		(result)->tv_sec = (a)->tv_sec - (b)->tv_sec;                          \
		(result)->tv_usec = (a)->tv_usec - (b)->tv_usec;                       \
		if ((result)->tv_usec < 0) {                                           \
			--(result)->tv_sec;                                                \
			(result)->tv_usec += 1000000;                                      \
		}                                                                      \
	} while (0)
#endif

namespace cml
{

class CTime
{
public:
	CTime() throw(): _t() { _t.tv_sec = 0; _t.tv_usec = 0; }
	CTime(time_t sec, suseconds_t usec) throw(): _t()
			{ _t.tv_sec = sec; _t.tv_usec = usec; }
	CTime(const CTime &t) throw(): _t(t._t) {}
	CTime(const timeval &t) throw(): _t(t) {}
	/// Constrcut a CTime from timespec.
	/// Value lower than microseconds is omitted.
	CTime(const timespec &t) throw(): _t()
			{ _t.tv_sec = t.tv_sec; _t.tv_usec = t.tv_nsec / 1000; }
	/// Construct a CTime in microseconds. Automatically carries if needed.
	CTime(unsigned time_us) throw(): _t()
			{ _t.tv_sec = time_us / 1000000L; _t.tv_usec = time_us % 1000000L; }
	/// Get the value of "second" part.
	inline time_t second() const throw() { return _t.tv_sec; }
	/// Set the value of "second" part.
	inline void setSecond(time_t s) throw() { _t.tv_sec = s; }
	/// Get the value of "microsecond" part.
	inline suseconds_t microsecond() const throw() { return _t.tv_usec; }
	/// Set the value of "microsecond" part.
	inline void setMicrosecond(suseconds_t s) throw() { _t.tv_usec = s; }
	/// Convert to struct timeval.
	inline timeval toTimeval() const throw() { return _t; }
	/// Convert to struct timespec.
	timespec toTimespec() const throw();
	/// Convert to string.
	std::string toString() const throw();

	// Operators.
	inline CTime& operator=(const CTime &o) throw() { _t = o._t; return *this; }
	CTime operator+(const CTime &o) throw();
	CTime operator-(const CTime &o) throw();
	CTime operator+=(const CTime &o) throw()
			{ *this = *this + o; return *this; }
	CTime operator-=(const CTime &o) throw()
			{ *this = *this - o; return *this; }
	bool operator>(const CTime &o) throw()
			{ return timercmp(&_t, &o._t, >); }
	bool operator<(const CTime &o) throw()
			{ return timercmp(&_t, &o._t, <); }
	bool operator!=(const CTime &o) throw()
			{ return timercmp(&_t, &o._t, !=); }
	bool operator==(const CTime &o) throw()
			{ return !timercmp(&_t, &o._t, !=); }
	bool operator>=(const CTime &o) throw()
			{ return !timercmp(&_t, &o._t, <); }
	bool operator<=(const CTime &o) throw()
			{ return !timercmp(&_t, &o._t, >); }

	/// Get current time of day.
	static CTime now() { CTime t; gettimeofday(&(t._t), NULL); return t; }

private:
	timeval _t;
};

}

extern std::ostream& operator<<(std::ostream &o, const cml::CTime &t);

#endif /* CTIME_H_ */
