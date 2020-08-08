#pragma once

#include <SFML/Graphics.hpp>

class Ship
{
	sf::RenderWindow* window;

	sf::Time deltaTime;

	//triangle
	int triangleSize = 30;
	sf::ConvexShape triangle;

	sf::Vector2<float> position;

	float rotationSpeed = 300.f;

	sf::Vector2f velocity;
	int maxVelocity = 300;

	bool isThrusting = false;
	float thrustPower = 600;

	

	sf::Vector2f forwardUnitVector;

	float drag = 50;

public:
	Ship(sf::RenderWindow& w);
	void Draw();
	void Update(sf::Time deltaTime);
	void Move();
	void GetInput();

	void PrintRotation();
	void GetVelocity();
};

