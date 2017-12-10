#ifndef MAPLE_PARSER_HPP
#define MAPLE_PARSER_HPP

#include <SFML\System\Vector2.hpp>
#include <string>

struct AppInfo
{
	std::string name;
	std::string description;
	sf::Vector2f dimensions;
	std::string properties;
	std::string author;
	std::string copyright;
	std::string github;
	std::string kunlauncher;
	std::string misc;
};

class MapleParser
{
public:
	MapleParser(std::string app);
	~MapleParser();

	AppInfo appInfo;

private:
	bool loadApp(std::string appdir);
	std::string getAppName(std::string settingsfile);
	std::string getAppDescription(std::string settingsfile);
	sf::Vector2f getAppDimensions(std::string settingsfile);
	void createApp();
};

#endif /* MAPLE_PARSER_HPP */
