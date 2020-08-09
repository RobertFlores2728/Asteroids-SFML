#include "Ship.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>


Ship::Ship(sf::RenderWindow& w) {
    window = &w;

    clear = sf::Color(0, 0, 255, 100);
    
    ship.setPointCount(3);
    ship.setPoint(0, sf::Vector2f(shipSize, shipSize/2));
    ship.setPoint(1, sf::Vector2f(0, 0));
    ship.setPoint(2, sf::Vector2f(0, shipSize));
    ship.setOrigin(shipSize/2, shipSize/2);
    ship.setOutlineColor(sf::Color::White);
    ship.setOutlineThickness(3);
    position.x = 500;
    position.y = 500;
    ship.setFillColor(clear);

    ship.setRotation(0.f); // rotations in sfml go in clockwise fashion
    

    ship.setPosition(shipSize, shipSize);

    texture.create(shipSize * 2, shipSize * 2);
    sprite = sf::Sprite(texture.getTexture());
    sprite.setPosition(position.x, position.y);
    sprite.setOrigin((shipSize * 2) / 2, (shipSize * 2) / 2);
    texture.clear(clear);
    texture.draw(ship);
    texture.display();
}

void Ship::Draw() {
    //texture.clear(clear);
    //texture.draw(ship);
    //texture.display();
    
    
    window->draw(sprite);
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
    sprite.setPosition(position.x, position.y);

    // screen wrapping effect
    if (sprite.getPosition().x > window->getSize().x)
        position.x = 0;
    else if (sprite.getPosition().x < 0)
        position.x = window->getSize().x;

    if (sprite.getPosition().y > window->getSize().y)
        position.y = 0;
    else if (sprite.getPosition().y < 0)
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
        sprite.setRotation(sprite.getRotation() - (rotationSpeed * deltaTime.asSeconds()));
        PrintRotation();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        sprite.setRotation(sprite.getRotation() + (rotationSpeed * deltaTime.asSeconds()));
        PrintRotation();
    }
}

void Ship::GetVelocity() {
    if (isThrusting) {
        // determine direction in which ship moves
        forwardUnitVector.x = std::cos(sprite.getRotation() * 3.141592 / 180.0); //cmath cos and sin functions take in radians but getRotation returns degrees. radians = degrees * pi / 180
        forwardUnitVector.y = std::sin(sprite.getRotation() * 3.141592 / 180.0);

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
    std::cout << "Angle: " << sprite.getRotation();
    std::cout << " Cosine: " << std::cos(sprite.getRotation() * 3.141592 / 180.0);
    std::cout << " Sine: " << std::sin(sprite.getRotation() * 3.141592 / 180.0) << std::endl;
}