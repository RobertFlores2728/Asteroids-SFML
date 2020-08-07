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
        velocity = thrust;
    }
    else {
        velocity = velocity - (drag * deltaTime.asSeconds());
        if (velocity < 0)
            velocity = 0;
    }

    sf::Vector2f forwardVector;
    forwardVector.x = std::cos(triangle.getRotation() * 3.141592 / 180.0); //cmath cos and sin functions take in radians but getRotation returns degrees. radians = degrees * pi / 180
    forwardVector.y = -std::sin(triangle.getRotation() * 3.141592 / 180.0); // negative since sfml rotations are in clockwise
    position.x = position.x + (velocity * forwardVector.x * deltaTime.asSeconds());
    position.y = position.y - (velocity * forwardVector.y * deltaTime.asSeconds());
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