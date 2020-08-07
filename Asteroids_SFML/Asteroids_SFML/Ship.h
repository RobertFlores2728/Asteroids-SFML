#pragma once

#include <SFML/Graphics.hpp>

class Ship
{
	//triangle
	int triangleSize = 30;
	sf::ConvexShape triangle;

	sf::Vector2<float> position;

	float rotationSpeed = 150.f;

	float velocity;

	bool isThrusting = false;
	float thrust = 250;

	float drag = 30;

public:
	Ship();
	void Draw(sf::RenderWindow& window);
	void Update(sf::Time deltaTime);
	void Move(sf::Time deltaTime);
	void GetInput(sf::Time deltaTime);

	void PrintRotation();
};

