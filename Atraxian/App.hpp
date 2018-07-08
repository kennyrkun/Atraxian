#ifndef APP_HPP
#define APP_HPP

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

class App
{
public:
	App();
	~App();

	AppInfo appInfo;
};

// app will the primary class for applications for atraxian
// it will have a pane if it wants to use one
//	perhaps it should extend from pane if it wants to be drawn
//  or maybe all apps should have a pane, and just not show it if they don't want to

#endif // !APP_HPP