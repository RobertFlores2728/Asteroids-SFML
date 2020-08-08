#pragma once

#include <SFML/Graphics.hpp>

class Asteroid
{
	sf::RenderWindow* window;

	sf::Time deltaTime;

	sf::ConvexShape asteroid;

	float asteroidSize = 50.f;

public:
	Asteroid(sf::RenderWindow& w);
	void Draw();
	void Update(sf::Time deltaTime);
};

