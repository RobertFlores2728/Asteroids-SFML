#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>
#include "Bullet.h"
#include "main.h"

class Bullet; // forward declaration fixes linking bugs!
class GameManager;
class Ship
{
private:
	GameManager* gm;

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

	

	

	float drag = 50;

	//Shooting timer
	sf::Clock shootingClock;
	int shootDelay = 0; // in milliseconds


public:

	sf::Vector2f forwardUnitVector;

	sf::Sprite shipSprite;

	sf::Vector2<float> position;

	//Class Functions
	Ship();
	Ship(GameManager& gameManager);
	void SetupConvexShape();
	void SetupSprite();

	void Draw();
	void Update(sf::Time dt);
	void Move();
	void GetInput();

	void PrintRotation();
	void GetVelocity();

	
	
};

