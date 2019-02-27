#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include <string>

namespace environment {

namespace filesystem
{
	bool exists(std::string thing_that_may_or_may_not_be_real);

	bool create_dir(std::string name, std::string dir);

	bool create_file(std::string name, std::string dir);

	bool move(std::string from, std::string to);

	bool remove(std::string thing_to_remove);

	bool rename(std::string dir, std::string file, std::string newname);
}

}

#endif /* FILESYSTEM_HPP */
