/**
 * \file StringHelper.h
 * \date Mar 6, 2010
 * \author samael
 */

#ifndef STRINGHELPER_H_
#define STRINGHELPER_H_

#include <vector>
#include <string>

namespace cml
{

/**
 * Helper functions for std::string.
 */
class StringHelper
{
public:
	static void tokens(const std::string &str, const std::string &delim,
			std::vector<std::string> *out_vec);
	static size_t strlcpy(char *dst, const char *src, size_t siz);
	static size_t strlcat(char *dst, const char *src, size_t siz);
};

}

#endif /* STRINGHELPER_H_ */
