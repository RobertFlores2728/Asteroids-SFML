#include "Asteroid.h"

Asteroid::Asteroid(GameManager& gameManager, sf::Vector2f forwardUV, sf::Vector2<float> pos, float speed, float size) {

	gm = &gameManager;

	asteroidSize = size;

	SetupConvexShape();
	SetupSprite();

	forwardUnitVector = forwardUV;

	position = pos;

	asteroidSpeed = speed;
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
	
	//asteroidSprite.setPosition(500, 500);
	gm->window->draw(asteroidSprite);

}

void Asteroid::Update(sf::Time dt) {
	this->deltaTime = dt;
	Move();
}



void Asteroid::Move() {
	velocity.x = asteroidSpeed * forwardUnitVector.x * deltaTime.asSeconds();
	velocity.y = asteroidSpeed * -forwardUnitVector.y * deltaTime.asSeconds();

	position.x += velocity.x * deltaTime.asSeconds();
	position.y -= velocity.y * deltaTime.asSeconds();
	asteroidSprite.setPosition(position.x, position.y);
	//std::cout << "Position: " << position.x << " " << position.y << std::endl;

	// screen wrapping effect
	if (asteroidSprite.getPosition().x > gm->window->getSize().x)
		position.x = 0;
	else if (asteroidSprite.getPosition().x < 0)
		position.x = gm->window->getSize().x;

	if (asteroidSprite.getPosition().y > gm->window->getSize().y)
		position.y = 0;
	else if (asteroidSprite.getPosition().y < 0)
		position.y = gm->window->getSize().y;
}