#ifndef APP_HPP
#define APP_HPP

#include <string>
#include <SFML\System\Vector2.hpp>

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

#endif // !APP_HPP