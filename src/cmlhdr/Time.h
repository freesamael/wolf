/**
 * \file Time.h
 * \date Jun 26, 2010
 * \author samael
 */

#ifndef TIME_H_
#define TIME_H_

#include <sys/time.h>
#include <cstddef>
#include <string>
#include <ostream>

namespace cml
{

class Time
{
public:
	Time(time_t sec = 0, suseconds_t usec = 0): _t()
		{ _t.tv_sec = sec; _t.tv_usec = usec; }
	Time(const timeval &t): _t(t) {}
	Time(const Time &t): _t(t._t) {}
	time_t second() const { return _t.tv_sec; }
	void setSecond(time_t s) { _t.tv_sec = s; }
	suseconds_t microsecond() const { return _t.tv_usec; }
	void setMicrosecond(suseconds_t s) { _t.tv_usec = s; }
	Time& operator=(const Time &o) { _t = o._t; return *this; }
	Time operator+(const Time &o);
	Time operator-(const Time &o);
	Time operator+=(const Time &o) { *this = *this + o; return *this; }
	Time operator-=(const Time &o) { *this = *this - o; return *this; }
	bool operator>(const Time &o) { return timercmp(&_t, &o._t, >); }
	bool operator<(const Time &o) { return timercmp(&_t, &o._t, <); }
	bool operator!=(const Time &o) { return timercmp(&_t, &o._t, !=); }
	bool operator==(const Time &o) { return !timercmp(&_t, &o._t, !=); }
	bool operator>=(const Time &o) { return !timercmp(&_t, &o._t, <); }
	bool operator<=(const Time &o) { return !timercmp(&_t, &o._t, >); }
	std::string toString() const;

	static Time now() { Time t; gettimeofday(&(t._t), NULL); return t; }

private:
	timeval _t;
};

}

extern std::ostream& operator<<(std::ostream &o, const cml::Time &t);

#endif /* TIME_H_ */
