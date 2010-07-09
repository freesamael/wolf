/**
 * \file CStringHelper.h
 * \date Mar 6, 2010
 * \author samael
 */

#ifndef CSTRINGHELPER_H_
#define CSTRINGHELPER_H_

#include <vector>
#include <string>

namespace cml
{

/**
 * Helper functions for std::string.
 */
class CStringHelper
{
public:
	static void tokens(const std::string &str, const std::string &delim,
			std::vector<std::string> *out_vec);
	static size_t strlcpy(char *dst, const char *src, size_t siz);
	static size_t strlcat(char *dst, const char *src, size_t siz);
};

}

#endif /* CSTRINGHELPER_H_ */
