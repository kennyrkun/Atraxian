#include "logger.hpp"

#include <filesystem>
#include <fstream>

namespace environment {

namespace filesystem
{
	namespace fs = std::experimental::filesystem;

	bool exists(std::string thing_that_may_or_may_not_be_real)
	{
		if (fs::exists(thing_that_may_or_may_not_be_real))
			return true;
		else
			return false;
	}

	bool create_dir(std::string name, std::string dir)
	{
		logger::INFO("Creating directory '" + name + "' in '" + dir + "'...");

		if (!exists(dir + "\\" + name)) // doesn't already exist
		{
			fs::create_directory(dir + "\\" + name);

			// make sure it was created.
			if (exists(name))
			{
				logger::INFO("Success!");
				return true;
			}
			else // something fucked up.
			{
				logger::INFO("Failed.");
				return false;
			}
		}
		else // is already a thing, skip.
		{
			logger::WARNING("Directory '" + name + "' already exists in '" + dir + "', skipping.");
			return false;
		}
	}

	bool create_file(std::string name, std::string dir)
	{
		logger::INFO("Creating file '" + name + "' in '" + dir + "'...");

		if (exists(dir + "\\" + name)) // if the file already exists
		{
			logger::WARNING("File '" + name + "' already exists in '" + dir + "', skipping.");
			return false;
		}
		else // does not exist, create it.
		{
			if (!exists(dir))
			{
				logger::WARNING("Specified directory does not exist, skipping.");
				return false;
			}
			else // directory exists, continue.
			{
				std::ofstream file_created(dir + "\\" + name);
				file_created.close();

				if (exists(dir + "\\" + name)) // file was created successfully.
				{
					logger::INFO("Success!");
					return true;
				}
				else // something fucked up.
				{
					logger::INFO("Failed.");
					return false;
				}
			}
		}
	}

	bool move(std::string file_or_dir, std::string to)
	{
		logger::INFO("Moving '" + file_or_dir + "' to '" + to + "'...");

		if (!exists(file_or_dir))
		{
			logger::ERROR("Specified file or directory does not exist.");
			return false;
		}
		else
		{
			if (exists(to))
			{
				if (exists(to + "\\" + file_or_dir))
				{
					fs::copy(file_or_dir, to);
					fs::remove(file_or_dir);

					logger::INFO("Success!");
					return true;
				}
				else // already exists
				{
					logger::INFO("Specified file or directory already exists in destination directory.");
					return false;
				}
			}
			else // destination does not exits
			{
				logger::ERROR("Specified destination directory does not exist.");
				return false;
			}
		}
	}

	bool remove(std::string thing_to_remove)
	{
		logger::INFO("Removing '" + thing_to_remove + "'.");

		if (exists(thing_to_remove))
		{
			fs::remove(thing_to_remove);

			if (!exists(thing_to_remove))
			{
				logger::INFO("Success!");
				return true;
			}
			else
			{
				logger::ERROR("Failed.");
				return false;
			}
		}
		else
		{
			logger::ERROR("Specified file does not exist.");
			return false;
		}
	}

	bool rename(std::string dir, std::string file, std::string newname)
	{
		logger::INFO("Renaming '" + file + "' to '" + newname + "'.");

		if (exists(dir + "\\" + file))
		{
			if (std::rename(file.c_str(), newname.c_str()) == 0)
			{
				logger::INFO("Success!");
				return true;
			}
			else
			{
				logger::ERROR("Failed.");
				return false;
			}
		}
		else
		{
			logger::ERROR("Specified file does not exist.");
			return false;
		}
	}
} // filesystem
}