#include "MapleParser.hpp"
#include "Filesystem.hpp"
#include "Logger.hpp"
#include "SettingsParser.hpp"

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

void MapleParser::createApp()
{
	logger::INFO("Created App!");
}
