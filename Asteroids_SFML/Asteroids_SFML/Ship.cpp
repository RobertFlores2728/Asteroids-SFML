#include "Ship.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>


Ship::Ship(sf::RenderWindow& w) {
    window = &w;
    
    triangle.setPointCount(3);
    triangle.setPoint(0, sf::Vector2f(triangleSize, triangleSize/2));
    triangle.setPoint(1, sf::Vector2f(0, 0));
    triangle.setPoint(2, sf::Vector2f(0, triangleSize));
    triangle.setOrigin(triangleSize/2, triangleSize/2);
    triangle.setOutlineColor(sf::Color::White);
    triangle.setOutlineThickness(3);
    position.x = 500;
    position.y = 500;
    triangle.setFillColor(sf::Color::Black);

    triangle.setRotation(0.f); // rotations in sfml go in clockwise fashion
    PrintRotation();
    
}

void Ship::Draw() {
    window->draw(triangle);
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
    triangle.setPosition(position.x, position.y);
}

void Ship::GetInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        isThrusting = true;
    }
    else {
        isThrusting = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        triangle.setRotation(triangle.getRotation() - (rotationSpeed * deltaTime.asSeconds()));
        PrintRotation();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        triangle.setRotation(triangle.getRotation() + (rotationSpeed * deltaTime.asSeconds()));
        PrintRotation();
    }
}

void Ship::GetVelocity() {
    if (isThrusting) {
        // determine direction in which ship moves
        forwardUnitVector.x = std::cos(triangle.getRotation() * 3.141592 / 180.0); //cmath cos and sin functions take in radians but getRotation returns degrees. radians = degrees * pi / 180
        forwardUnitVector.y = -std::sin(triangle.getRotation() * 3.141592 / 180.0); // negative since sfml rotations are in clockwise

        // velocity is equal to the thrust power times the unit vector direction of movement
        velocity.x += thrustPower * forwardUnitVector.x * deltaTime.asSeconds();
        velocity.y += thrustPower * forwardUnitVector.y * deltaTime.asSeconds();

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
    std::cout << "Angle:" << triangle.getRotation();
    std::cout << " Cosine: " << std::cos(triangle.getRotation() * 3.141592 / 180.0);
    std::cout << " Sine: " << std::sin(triangle.getRotation() * 3.141592 / 180.0) << std::endl;
}