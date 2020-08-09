#pragma once

#include <SFML/Graphics.hpp>
#include "Ship.h"

class Asteroid
{
	sf::RenderWindow* window;

	sf::RenderTexture texture;
	sf::Sprite sprite;
	sf::Color clear;

	sf::Time deltaTime;

	sf::ConvexShape asteroid;

	float asteroidSize = 50.f;

	Ship* ship;

public:
	Asteroid(sf::RenderWindow& w, Ship& s);
	void SetupConvexShape();
	void SetPolygonPoints();
	void SetupSprite();

	void Draw();
	void Update(sf::Time deltaTime);

	void CheckShipCollision();
};

