#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "main.h"
#include "Collision.h"
#include "Ship.h"

class Ship;
class Asteroid
{
	sf::RenderWindow* window;

	sf::RenderTexture asteroidTexture;
	sf::Sprite asteroidSprite;
	sf::Color clear;

	sf::Time deltaTime;

	sf::ConvexShape asteroidShape;

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

