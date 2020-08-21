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
class GameManager;
class Asteroid
{
	GameManager* gm;

	sf::RenderTexture asteroidTexture;
	sf::Color clear;

	sf::Time deltaTime;

	sf::ConvexShape asteroidShape;

	

	


	//Movement
	sf::Vector2f velocity;
	float asteroidSpeed;
	sf::Vector2f forwardUnitVector;

public:
	sf::Vector2<float> position;
	float asteroidSize;

	sf::Sprite asteroidSprite;

	Asteroid(GameManager& gameManager, sf::Vector2f forwardUV, sf::Vector2<float> pos, float speed, float size);
	void SetupConvexShape();
	void SetPolygonPoints();
	void SetupSprite();

	void Draw();
	void Update(sf::Time deltaTime);
	void Move();

	
};

