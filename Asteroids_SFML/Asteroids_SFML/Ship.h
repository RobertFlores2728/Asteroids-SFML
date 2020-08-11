#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Bullet.h"

class Bullet; // forward declaration fixes linking bugs!
class Ship
{
private:
	sf::RenderWindow* window;

	sf::Time deltaTime;

	//triangle
	int shipSize = 30;
	sf::ConvexShape shipShape;
	sf::RenderTexture shipTexture;
	

	sf::Color clear;


	float rotationSpeed = 300.f;

	sf::Vector2f velocity;
	int maxVelocity = 300;

	bool isThrusting = false;
	float thrustPower = 600;

	

	sf::Vector2f forwardUnitVector;

	float drag = 50;

	//Shooting timer
	sf::Clock shootingClock;
	int shootDelay = 0; // in milliseconds


public:
	//Bullets
	std::vector<Bullet*> bullets;

	sf::Sprite shipSprite;

	sf::Vector2<float> position;

	//Class Functions
	Ship();
	Ship(sf::RenderWindow& w);
	void SetupConvexShape();
	void SetupSprite();

	void Draw();
	void Update(sf::Time dt);
	void Move();
	void GetInput();

	void PrintRotation();
	void GetVelocity();

	//Bullets
	
	void UpdateBullets();
	void ShootBullet();
	
};

