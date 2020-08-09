#pragma once

#include <SFML/Graphics.hpp>

class Asteroid
{
	sf::RenderWindow* window;

	sf::RenderTexture texture;
	sf::Sprite sprite;
	sf::Color clear;

	sf::Time deltaTime;

	sf::ConvexShape asteroid;

	float asteroidSize = 50.f;

public:
	Asteroid(sf::RenderWindow& w);
	void SetupConvexShape();
	void SetPolygonPoints();

	void Draw();
	void Update(sf::Time deltaTime);
};

