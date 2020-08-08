#include "Asteroid.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

Asteroid::Asteroid(sf::RenderWindow& w) {
	window = &w;

	std::srand((int)std::time(0));
	int numPoints = 5 + rand() % (3 + 1);


	asteroid.setPointCount(numPoints);

	std::cout << "Num of points: " << numPoints << std::endl;

	int degreesPerPoint = (int)(360 / numPoints);
	std::cout << "Degrees per point: " << degreesPerPoint << std::endl;
	

	float totalAngle = 1;

	for (int i = 0; i < numPoints; i++) {
		std::cout << "now on point: " << i << ". ";
		
		std::cout << "Angle: " << totalAngle;
		std::cout << " Cosine: " << std::cos(totalAngle * 3.141592 / 180.0);
		std::cout << " Sine: " << std::sin(totalAngle * 3.141592 / 180.0) << std::endl;

		sf::Vector2f position;
		position.x = std::cos(totalAngle * 3.141592 / 180.0) * asteroidSize;
		position.y = std::sin(totalAngle * 3.141592 / 180.0) * asteroidSize;

		//add point to convex shape
		asteroid.setPoint(i, sf::Vector2f(position.x, -position.y));

		totalAngle += degreesPerPoint;
		
	}

	asteroid.setOutlineColor(sf::Color::White);
	asteroid.setOutlineThickness(3);
	asteroid.setFillColor(sf::Color::Black);
	asteroid.setPosition(500, 500);


}

void Asteroid::Draw() {
	window->draw(asteroid);
}

void Asteroid::Update(sf::Time dt) {
	this->deltaTime = dt;
}