#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>

namespace logger
{
	void INFO(std::string output);

	void WARNING(std::string output);

	void ERROR(std::string output);

	void SILENT(std::string output);
}

#endif
