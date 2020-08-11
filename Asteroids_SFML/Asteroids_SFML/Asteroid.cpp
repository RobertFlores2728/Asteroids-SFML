#include "Asteroid.h"

Asteroid::Asteroid(sf::RenderWindow& w, Ship& s) {
	window = &w;
	ship = &s;

	SetupConvexShape();
	SetupSprite();


}

void Asteroid::SetupConvexShape() {
	SetPolygonPoints();

	clear = sf::Color(0, 0, 0, 0);

	asteroidShape.setOutlineColor(sf::Color::White);
	asteroidShape.setOutlineThickness(3);
	asteroidShape.setFillColor(clear);
	asteroidShape.setOrigin(asteroidSize, asteroidSize);
	asteroidShape.setPosition(asteroidSize * 2.5, asteroidSize * 2.2);

	
}

void Asteroid::SetupSprite() {
	//create texture to hold shape
	asteroidTexture.create(asteroidSize * 2.5, asteroidSize * 2.5);
	asteroidTexture.clear(clear);
	asteroidTexture.draw(asteroidShape);
	asteroidTexture.display();

	asteroidSprite = sf::Sprite(asteroidTexture.getTexture());
}

void Asteroid::SetPolygonPoints() {
	// get random points number to make polygon. pentagon, hexagon, etc.
	std::srand((int)std::time(0));
	int numPoints = 5 + rand() % (3 + 1);


	asteroidShape.setPointCount(numPoints);

	
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
		asteroidShape.setPoint(i, sf::Vector2f(position.x, -position.y));

		totalAngle += degreesPerPoint;

	}
}

void Asteroid::Draw() {
	
	asteroidSprite.setPosition(500, 500);
	window->draw(asteroidSprite);

}

void Asteroid::Update(sf::Time dt) {
	this->deltaTime = dt;
	CheckShipCollision();
}

void Asteroid::CheckShipCollision() {
	if (Collision::BoundingBoxTest(asteroidSprite, ship->shipSprite)) {
		//std::cout << "Collision - Bounding box!" << std::endl;

		if (Collision::PixelPerfectTest(asteroidSprite, ship->shipSprite)) {
			std::cout << "Collision - Pixel perfect!" << std::endl;
		}
	}
}