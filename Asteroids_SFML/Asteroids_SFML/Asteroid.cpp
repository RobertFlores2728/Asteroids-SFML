#include "Asteroid.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "main.h"
#include "Collision.h"
#include "Ship.h"

Asteroid::Asteroid(sf::RenderWindow& w, Ship& s) {
	window = &w;
	ship = &s;

	SetupConvexShape();
	SetupSprite();


}

void Asteroid::SetupConvexShape() {
	SetPolygonPoints();

	clear = sf::Color(0, 0, 0, 0);

	asteroid.setOutlineColor(sf::Color::White);
	asteroid.setOutlineThickness(3);
	asteroid.setFillColor(clear);
	asteroid.setOrigin(asteroidSize, asteroidSize);
	asteroid.setPosition(asteroidSize * 2.5, asteroidSize * 2.2);

	
}

void Asteroid::SetupSprite() {
	//create texture to hold shape
	texture.create(asteroidSize * 2.5, asteroidSize * 2.5);
	texture.clear(clear);
	texture.draw(asteroid);
	texture.display();

	sprite = sf::Sprite(texture.getTexture());
}

void Asteroid::SetPolygonPoints() {
	// get random points number to make polygon. pentagon, hexagon, etc.
	std::srand((int)std::time(0));
	int numPoints = 5 + rand() % (3 + 1);


	asteroid.setPointCount(numPoints);

	
	// draw a point every amount of degrees around a circle. 8 sided polygon = 360/8 = 45 degrees per point
	int degreesPerPoint = (int)(360 / numPoints);

	// tracks the current angle where a point is drawn to
	float totalAngle = 1;

	// set each point in the sf::ConvexShape object
	for (int i = 0; i < numPoints; i++) {

		sf::Vector2f position; // position of point
		int offset = -(1 + rand() % (14 + 1)); // in order to make asteroids look deform and more varied
		position.x = std::cos(totalAngle * 3.141592 / 180.0) * asteroidSize + offset; // x position of point
		position.y = std::sin(totalAngle * 3.141592 / 180.0) * asteroidSize + offset; // y position of point

		//add the point to the convex shape
		asteroid.setPoint(i, sf::Vector2f(position.x, -position.y));

		totalAngle += degreesPerPoint;

	}
}

void Asteroid::Draw() {
	
	sprite.setPosition(500, 500);
	window->draw(sprite);

}

void Asteroid::Update(sf::Time dt) {
	this->deltaTime = dt;
	CheckShipCollision();
}

void Asteroid::CheckShipCollision() {
	if (Collision::BoundingBoxTest(sprite, ship->sprite)) {
		//std::cout << "Collision - Bounding box!" << std::endl;

		if (Collision::PixelPerfectTest(sprite, ship->sprite)) {
			std::cout << "Collision - Pixel perfect!" << std::endl;
		}
	}
}