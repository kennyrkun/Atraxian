#include "MapleParser.hpp"
#include "Filesystem.hpp"
#include "Logger.hpp"
#include "SettingsParser.hpp"

#include <fstream>
#include <limits>

std::ifstream& GotoLine(std::ifstream& file, unsigned int num)
{
    file.seekg(std::ios::beg);

    for(size_t i = 0; i < num - 1; ++i)
	{
        file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }

    return file;
}

// --PUBLIC

MapleParser::MapleParser(std::string app)
{
	logger::CUSTOM("MAPLE", "MapleParser initialised.");

	loadApp(app);
}

MapleParser::~MapleParser()
{
	logger::CUSTOM("MAPLE", "Finished.");
}

// --PRIVATE

bool MapleParser::loadApp(std::string appdir)
{
	logger::CUSTOM("MAPLE", "Attempting to load app '" + appdir + "'...");

	if (environment::filesystem::exists(appdir))
	{
		std::string dir = appdir + "//";

		std::string tempname = appdir.substr(appdir.find_last_of('//'), appdir.length());

		if (environment::filesystem::exists(dir + "main.mpl"))
		{
			logger::CUSTOM("MAPLE", "Found main.mpl for `" + appdir + "`.");

			if (environment::filesystem::exists(dir + tempname + ".conf"))
			{
				SettingsParser getAppSettings;
				getAppSettings.loadFromFile(dir + tempname + ".conf");

				getAppSettings.get("appName", appInfo.name);
				getAppSettings.get("description", appInfo.description);
				getAppSettings.get("dimensions", appInfo.dimensions);
				getAppSettings.get("author", appInfo.author);
				getAppSettings.get("copyright", appInfo.copyright);
				getAppSettings.get("properties", appInfo.properties);
				getAppSettings.get("kunlauncher", appInfo.kunlauncher);
				getAppSettings.get("github", appInfo.github);
				getAppSettings.get("misc", appInfo.misc);

				createApp();

				return true;
			}
			else // settings.cfg
			{
				logger::CUSTOM("MAPLE", "No " + appdir + ".conf file was found for '" + appdir + "', aborting.");

				return false;
			}
		}
		else // main.mpl
		{
			logger::CUSTOM("MAPLE", "Folder for `" + appdir + "` was found, but main.mpl was not. Aborting.");

			return false;
		}
	}
	else
	{
		logger::CUSTOM("MAPLE", "Could not find main.mpl for `" + appdir + "`.");

		return false;
	}
}

std::string MapleParser::getAppName(std::string settingsfile)
{
	logger::CUSTOM("MAPLE", "Finding app name...");

	if (environment::filesystem::exists(settingsfile))
	{
		std::ifstream getSettings(settingsfile);

		if (getSettings.is_open())
		{
			GotoLine(getSettings, 1);
			std::string name;
			getline(getSettings, name);
			name.erase(0, 10);
			name.erase(name.end() - 1, name.end());

			logger::CUSTOM("MAPLE", "App = \"" + name + "\".");

			return name;
		}
		else
		{
			logger::CUSTOM("MAPLE-ERROR", "Failed to open settings file!");

			return "FAILED";
		}
	}
	else
	{
		logger::CUSTOM("MAPLE-ERROR", "Could not find settings.cfg!");

		return "FAILED";
	}
}

std::string MapleParser::getAppDescription(std::string settingsfile)
{
	logger::CUSTOM("MAPLE", "Finding description...");

	if (environment::filesystem::exists(settingsfile))
	{
		std::ifstream getDescription(settingsfile);

		if (getDescription.is_open())
		{
			GotoLine(getDescription, 2);
			std::string description;
			getline(getDescription, description);
			description.erase(0, 13); // description="
			description.erase(description.end() - 1, description.end()); // "

			logger::CUSTOM("MAPLE", "Desc = \"" + description + "\".");

			return description;
		}
		else
		{
			logger::CUSTOM("MAPLE-ERROR", "Failed to open settings file!");

			return "FAILED";
		}
	}
	else
	{
		logger::CUSTOM("MAPLE-ERROR", "Could not find settings.cfg!");

		return "FAILED";
	}
}

sf::Vector2f MapleParser::getAppDimensions(std::string settingsfile)
{
	if (environment::filesystem::exists(settingsfile))
	{
		SettingsParser getDimensions;
		getDimensions.loadFromFile(settingsfile);

		sf::Vector2f dimensions;
		getDimensions.get("dimensions", dimensions);

		return dimensions;
	}
	else
	{
		logger::CUSTOM("MMAPLE-ERROR", "Could not find settings.cfg!");

		return sf::Vector2f(0, 0);
	}
}

void MapleParser::createApp()
{
	logger::INFO("Created App!");
}
