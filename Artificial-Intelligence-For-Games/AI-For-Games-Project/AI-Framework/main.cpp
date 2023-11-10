#include <iostream>
#include <SFML/Graphics.hpp>

#include "GridManager.h"
#include "BaseEntity.h"
#include "UtilRandom.h"
#include "Constants.h"
#include "Hunter.h"
#include "Prey.h"

// I should be looking to eventually get all of the logic for the states into the state.cpp file. Check for reference

int main()
{
	// construct a window
	sf::RenderWindow window(sf::VideoMode(ScreenWidth, ScreenHeight), "s233122");
	window.setFramerateLimit(60.0f);
	// because we're running as a console application, we still get access to the console, so can use std::cout to print to it
	std::cout << "Constructed SFML Window" << std::endl;

	std::vector<BaseEntity*> entities;

	entities.push_back(new Hunter());
	entities.push_back(new Prey((Hunter*)entities[0]));
	entities.push_back(new HunterHome);

	for (int i = 0; i < entities.size(); ++i)
	{
		entities[i]->Initialize();
	}

	GridManager _grid;

	auto hunter = static_cast<Hunter*>(entities[0]);

	hunter->prey = entities[1];
	hunter->home = entities[2];
	hunter->_grid = &_grid;

	//auto hunterHomeGrid = _grid.getGridPosition(entities[2]->getPosition().x, entities[2]->getPosition().y);

	sf::Clock dt;

	// our game loop
	while (window.isOpen())
	{
		// poll for events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					for (BaseEntity* agent : BaseEntity::Renderables)
					{
						agent->RandomisePosition();
					}
				}

				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
			}
		}

		// clear the window before drawing anything to it
		window.clear();

		float delta = dt.restart().asSeconds();

		// update all our entities

		for (auto entity : BaseEntity::Renderables)
		{
			entity->Update(delta);
		}

		for (auto entity : BaseEntity::Renderables)
		{
			entity->Think(delta);
		}

		// and then draw them
		for (auto entity : BaseEntity::Renderables)
		{
			window.draw(entity->GetSprite(), entity->getTransform());
		}

		_grid.DrawGrid(window);

		// swap the frame buffers
		window.display();
	}

	return 0;
}