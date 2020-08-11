#pragma once

#include <SFML/Graphics.hpp>
//#include "Ship.h"

class Bullet
{
private:
	sf::RenderWindow* window;
	sf::Time deltaTime;

	sf::Color clear;

	sf::Vector2<float> position;

	sf::Vector2f velocity;
	float bulletSpeed = 30.0f;


	//bullet shape
	int bulletSize = 30;
	sf::CircleShape bulletShape;
	sf::RenderTexture bulletTexture;

	

public:
	sf::Sprite bulletSprite;

	//Ship* ship;

	Bullet();
	Bullet(sf::RenderWindow& w);//, Ship& s);

	void SetupCircleShape();
	//void SetupSprite();

	void Draw();
	void Update(sf::Time dt);
	//void Move();


};

