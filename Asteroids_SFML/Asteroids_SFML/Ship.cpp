#include "Ship.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>


Ship::Ship() {
    
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

void Ship::Draw(sf::RenderWindow& window) {
    window.draw(triangle);
}

void Ship::Update(sf::Time deltaTime) {
    GetInput(deltaTime);
    Move(deltaTime);

}

void Ship::Move(sf::Time deltaTime) {
    
    if (isThrusting) {
        forwardVector.x = std::cos(triangle.getRotation() * 3.141592 / 180.0); //cmath cos and sin functions take in radians but getRotation returns degrees. radians = degrees * pi / 180
        forwardVector.y = -std::sin(triangle.getRotation() * 3.141592 / 180.0); // negative since sfml rotations are in clockwise

        thrustDirectionVector.x = thrustPower * forwardVector.x;
        thrustDirectionVector.y = thrustPower * forwardVector.y;

        velocity.x += thrustDirectionVector.x * deltaTime.asSeconds();
        velocity.y += thrustDirectionVector.y * deltaTime.asSeconds();

        if (velocity.x > maxVelocity)
            velocity.x = maxVelocity;
        if (velocity.y > maxVelocity)
            velocity.y = maxVelocity;
    }
    else {
        velocity.x = velocity.x - (drag * deltaTime.asSeconds());
        if (velocity.x < -maxVelocity)
            velocity.x = -maxVelocity;
        velocity.y = velocity.y - (drag * deltaTime.asSeconds());
        if (velocity.y < -maxVelocity)
            velocity.y = -maxVelocity;
    }

    
    position.x += velocity.x * deltaTime.asSeconds();
    position.y -= velocity.y * deltaTime.asSeconds();
    triangle.setPosition(position.x, position.y);
}

void Ship::GetInput(sf::Time deltaTime) {
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

void Ship::PrintRotation() {
    std::cout << "Angle:" << triangle.getRotation();
    std::cout << " Cosine: " << std::cos(triangle.getRotation() * 3.141592 / 180.0);
    std::cout << " Sine: " << std::sin(triangle.getRotation() * 3.141592 / 180.0) << std::endl;
}