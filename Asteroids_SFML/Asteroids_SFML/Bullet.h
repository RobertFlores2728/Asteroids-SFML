#pragma once

#include <SFML/Graphics.hpp>
#include "Ship.h"

//forward decleration
class Ship;

class Bullet
{
private:
	sf::RenderWindow* window;
	sf::Time deltaTime;

	sf::Color clear;

	sf::Vector2<float> position;

	sf::Vector2f velocity;
	float bulletSpeed = 10 * 10000.0f;
	sf::Vector2f forwardUnitVector;


	//bullet shape
	int bulletSize = 3;
	sf::CircleShape bulletShape;
	sf::RenderTexture bulletTexture;

	//Bullet life timer
	sf::Clock bulletClock;
	int bulletLife = 3; // in seconds

public:
	sf::Sprite bulletSprite;

	Ship* ship;

	Bullet();
	Bullet(sf::RenderWindow& w, Ship& s);

	void SetupCircleShape();
	void SetupSprite();

	void Draw();
	void Update(sf::Time dt);
	void Move();

	bool CheckIfLifeOver();

};

