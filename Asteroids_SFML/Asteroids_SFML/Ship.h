#pragma once

#include <SFML/Graphics.hpp>

class Ship
{
	sf::RenderWindow* window;

	sf::Time deltaTime;

	//triangle
	int shipSize = 30;
	sf::ConvexShape ship;
	sf::RenderTexture texture;
	

	sf::Color clear;

	sf::Vector2<float> position;

	float rotationSpeed = 300.f;

	sf::Vector2f velocity;
	int maxVelocity = 300;

	bool isThrusting = false;
	float thrustPower = 600;

	

	sf::Vector2f forwardUnitVector;

	float drag = 50;

public:
	sf::Sprite sprite;

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
};

