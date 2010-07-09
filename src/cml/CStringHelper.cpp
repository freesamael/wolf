/**
 * \file CStringHelper.cpp
 * \date Mar 6, 2010
 * \author samael
 */

#include <cstring>
#include "CStringHelper.h"

using namespace std;

namespace cml
{

/**
 * strtok() equivalent C++ function.
 *
 * \param[in] str
 * String to process.
 *
 * \param[in] delim
 * Symbols to split the string.
 *
 * \param[out] out_vec
 * results.
 *
 * \note
 * The original elements in out_vec will be erased before returning.
 */
void CStringHelper::tokens(const string &str, const string &delim,
		vector<string> *out_vec)
{
	string::size_type pos_begin, pos_end;

	/* Initially skip all delims appear at the beginning of the string.
	 * This avoids generating an empty string in the extracted tokens.
	 */
	pos_begin = pos_end = str.find_first_not_of(delim);

	// Clear the vector first.
	out_vec->clear();

	// Extract tokens.
	while (pos_begin < string::npos) {
		pos_end = str.find_first_of(delim, pos_begin);
		out_vec->push_back(str.substr(pos_begin, pos_end - pos_begin));
		pos_begin = str.find_first_not_of(delim, pos_end);
	}
}

/**
 * Copy src to string dst of size siz.  At most siz-1 characters
 * will be copied.  Always NUL terminates (unless siz == 0).
 * Returns strlen(src); if retval >= siz, truncation occurred.
 *
 * \note
 * Taken from BSD implementation.
 */
size_t CStringHelper::strlcpy(char *dst, const char *src, size_t siz)
{
	char *d = dst;
	const char *s = src;
	size_t n = siz;

	/* Copy as many bytes as will fit */
	if (n != 0) {
		while (--n != 0) {
			if ((*d++ = *s++) == '\0')
				break;
		}
	}

	/* Not enough room in dst, add NUL and traverse rest of src */
	if (n == 0) {
		if (siz != 0)
			*d = '\0';		/* NUL-terminate dst */
		while (*s++)
			;
	}

	return(s - src - 1);	/* count does not include NUL */

}

/**
 * Appends src to string dst of size siz (unlike strncat, siz is the
 * full size of dst, not space left).  At most siz-1 characters
 * will be copied.  Always NUL terminates (unless siz <= strlen(dst)).
 * Returns strlen(src) + MIN(siz, strlen(initial dst)).
 * If retval >= siz, truncation occurred.
 *
 * \note
 * Taken from BSD implementation.
 */
size_t CStringHelper::strlcat(char *dst, const char *src, size_t siz)
{
	char *d = dst;
	const char *s = src;
	size_t n = siz;
	size_t dlen;

	/* Find the end of dst and adjust bytes left but don't go past end */
	while (n-- != 0 && *d != '\0')
		d++;
	dlen = d - dst;
	n = siz - dlen;

	if (n == 0)
		return(dlen + strlen(s));
	while (*s != '\0') {
		if (n != 1) {
			*d++ = *s;
			n--;
		}
		s++;
	}
	*d = '\0';

	return(dlen + (s - src));	/* count does not include NUL */
}

}
