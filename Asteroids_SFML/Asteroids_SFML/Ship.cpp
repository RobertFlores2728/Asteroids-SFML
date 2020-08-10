#include "Ship.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <ctime>

Ship::Ship() {}


Ship::Ship(sf::RenderWindow& w) {
    window = &w;

    clear = sf::Color(0, 0, 0, 0);
    
    SetupConvexShape();

    SetupSprite();

}

void Ship::SetupConvexShape() {
    shipShape.setPointCount(3);
    shipShape.setPoint(0, sf::Vector2f(shipSize, shipSize / 2));
    shipShape.setPoint(1, sf::Vector2f(0, 0));
    shipShape.setPoint(2, sf::Vector2f(0, shipSize));
    shipShape.setOrigin(shipSize / 2, shipSize / 2);
    shipShape.setOutlineColor(sf::Color::White);
    shipShape.setOutlineThickness(3);
    shipShape.setFillColor(clear);

    shipShape.setRotation(0.f); // rotations in sfml go in clockwise fashion


    shipShape.setPosition(shipSize, shipSize);
}

void Ship::SetupSprite() {
    position.x = 500;
    position.y = 500;

    shipTexture.create(shipSize * 2, shipSize * 2);
    shipSprite = sf::Sprite(shipTexture.getTexture());
    shipSprite.setPosition(position.x, position.y);
    shipSprite.setOrigin((shipSize * 2) / 2, (shipSize * 2) / 2);
    shipTexture.clear(clear);
    shipTexture.draw(shipShape);
    shipTexture.display();
}

void Ship::Draw() {
    
    window->draw(shipSprite);
}

void Ship::Update(sf::Time dt) {
    deltaTime = dt;
    GetInput();
    GetVelocity();
    Move();
}

void Ship::Move() {
    position.x += velocity.x * deltaTime.asSeconds();
    position.y -= velocity.y * deltaTime.asSeconds();
    shipSprite.setPosition(position.x, position.y);

    // screen wrapping effect
    if (shipSprite.getPosition().x > window->getSize().x)
        position.x = 0;
    else if (shipSprite.getPosition().x < 0)
        position.x = window->getSize().x;

    if (shipSprite.getPosition().y > window->getSize().y)
        position.y = 0;
    else if (shipSprite.getPosition().y < 0)
        position.y= window->getSize().y;
}

void Ship::GetInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        isThrusting = true;
    }
    else {
        isThrusting = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        shipSprite.setRotation(shipSprite.getRotation() - (rotationSpeed * deltaTime.asSeconds()));
        PrintRotation();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        shipSprite.setRotation(shipSprite.getRotation() + (rotationSpeed * deltaTime.asSeconds()));
        PrintRotation();
    }

    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        sf::Time now = shootingClock.getElapsedTime();
        if (now.asMilliseconds() > shootDelay) {
            ShootBullet();
            shootDelay = 1000;
            shootingClock.restart();
        }

    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        shootDelay = 200;
    }

    


}

void Ship::GetVelocity() {
    if (isThrusting) {
        // determine direction in which ship moves
        forwardUnitVector.x = std::cos(shipSprite.getRotation() * 3.141592 / 180.0); //cmath cos and sin functions take in radians but getRotation returns degrees. radians = degrees * pi / 180
        forwardUnitVector.y = std::sin(shipSprite.getRotation() * 3.141592 / 180.0);

        // velocity is equal to the thrust power times the unit vector direction of movement
        velocity.x += thrustPower * forwardUnitVector.x * deltaTime.asSeconds();
        // subtract since sfml rotations are in clockwise. this is due to the fact that in sfml(and other graphics libraries), y = 0 refers to top of screen and increments positively as it goes down the screen.
        velocity.y -= thrustPower * forwardUnitVector.y * deltaTime.asSeconds();

        //velocity caps
        if (velocity.x > maxVelocity)
            velocity.x = maxVelocity;
        else if (velocity.x < -maxVelocity)
            velocity.x = -maxVelocity;

        
        if (velocity.y > maxVelocity)
            velocity.y = maxVelocity;
        else if (velocity.y < -maxVelocity)
            velocity.y = -maxVelocity;
    }
    else {
        // else the velocity is decremented or incremented towards 0 by the drag value
        if (velocity.x > 0)
            velocity.x -= (drag * deltaTime.asSeconds());
        else if (velocity.x < 0)
            velocity.x += (drag * deltaTime.asSeconds());

        if (velocity.y > 0)
            velocity.y -= (drag * deltaTime.asSeconds());
        else if (velocity.y < 0)
            velocity.y += (drag * deltaTime.asSeconds());
    }
}

void Ship::PrintRotation() {
    std::cout << "Angle: " << shipSprite.getRotation();
    std::cout << " Cosine: " << std::cos(shipSprite.getRotation() * 3.141592 / 180.0);
    std::cout << " Sine: " << std::sin(shipSprite.getRotation() * 3.141592 / 180.0) << std::endl;
}


void Ship::UpdateBullets() {
    
}
void Ship::ShootBullet() {
    std::cout << "Bullet shot!" << std::endl;
}