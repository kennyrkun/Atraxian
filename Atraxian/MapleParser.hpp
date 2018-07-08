#ifndef MAPLE_PARSER_HPP
#define MAPLE_PARSER_HPP

#include "App.hpp"

#include <SFML\System\Vector2.hpp>

#include <string>

class MapleParser
{
public:
	MapleParser(std::string app);
	~MapleParser();

	AppInfo appInfo;

private:
	bool loadApp(std::string appdir);
	void createApp();
};

// perhaps maple parser should do nothing in the constructor, instead it should have a function
// seperaterly that can be called which will return an object of the class App

#endif /* MAPLE_PARSER_HPP */
