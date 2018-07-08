#include "Environment.hpp"
#include "Logger.hpp"

#include <SFML\Graphics.hpp>

#include <iostream>
#include <thread>
#include <string>

int mai2n();

void main()
{
	{
		bool right(false);

		do
		{
			std::cout << "view (T)est or (A)traxian" << std::endl;
			std::string line;
			std::getline(std::cin, line);

			if (line == "a")
			{
				mai2n();
			}
			else if (line == "t")
			{
				right = true;
			}
			else
			{
				std::cout << "wrong" << std::endl;
			}
		} while (!right);
	}

	sf::RenderWindow window(sf::VideoMode(800, 600), "title");
	window.setVerticalSyncEnabled(true);

	bool dragging(false);
	sf::Vector2f click_pos;
	sf::RectangleShape shape;
	shape.setOutlineThickness(1);
	shape.setOutlineColor(sf::Color(51, 153, 255));
	shape.setFillColor(sf::Color(51, 153, 255, 50));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::EventType::MouseMoved)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					shape.setSize(sf::Vector2f(sf::Mouse::getPosition(window).x - click_pos.x, sf::Mouse::getPosition(window).y - click_pos.y));
				}
			}
			else if (event.type == sf::Event::EventType::MouseButtonPressed)
			{
				if (event.key.code == sf::Mouse::Button::Left)
				{
					click_pos = sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
					shape.setPosition(click_pos);

					dragging = true;
				}
			}
			else if (event.type == sf::Event::EventType::MouseButtonReleased)
			{
				if (event.key.code == sf::Mouse::Button::Left && dragging)
				{
					shape.setSize(sf::Vector2f(0, 0));

					dragging = false;
				}
			}
		}

		window.clear();

		window.draw(shape);

		window.display();
	}
}

void new_Env(int envID)
{
	Environment *atraxian = new Environment(sf::VideoMode(1080, 720), ("AtraxiaN-" + ENVIRONMENT_VERSION), envID);
	atraxian->main();
	delete atraxian;
}

int mai2n()
{
	logger::INFO("Initlializing Atraxian " + ENVIRONMENT_VERSION + "...");
	logger::BREAK();

	std::thread one(new_Env, 1);
	one.join();

	logger::INFO("Exiting...");

	std::cin.get();
	return 0;
}
