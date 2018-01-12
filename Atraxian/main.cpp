#include "Environment.hpp"
#include "Logger.hpp"

#include <SFML\Graphics\RenderWindow.hpp>

#include <iostream>
#include <thread>

void new_Env(int envID)
{
	Environment *atraxian = new Environment(sf::VideoMode(1080, 720), ("AtraxiaN-" + ENVIRONMENT_VERSION), envID);
	atraxian->main();
	delete atraxian;
}

int main()
{
	logger::INFO("Initlializing Atraxian " + ENVIRONMENT_VERSION + "...");
	logger::BREAK();

	std::thread one(new_Env, 1);
	one.join();

	logger::INFO("Exiting...");

	std::cin.get();
	return 0;
}
