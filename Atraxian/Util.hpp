 #ifndef UTIL_HPP
#define UTIL_HPP

#include <string>

namespace environment {

namespace util
{
	std::string getTimestamp();

	bool fs_ready();

	void ready_fs();
}

}

#endif
