#pragma once

#include <SFML/Graphics.hpp>

class Ship
{
	//triangle
	int triangleSize = 30;
	sf::ConvexShape triangle;

	sf::Vector2<float> position;

	float rotationSpeed = 200.f;

	sf::Vector2f velocity;
	int maxVelocity = 300;

	bool isThrusting = false;
	float thrustPower = 300;

	

	sf::Vector2f forwardUnitVector;

	float drag = 50;

public:
	Ship();
	void Draw(sf::RenderWindow& window);
	void Update(sf::Time deltaTime);
	void Move(sf::Time deltaTime);
	void GetInput(sf::Time deltaTime);

	void PrintRotation();
	void GetVelocity(sf::Time deltaTime);
};

