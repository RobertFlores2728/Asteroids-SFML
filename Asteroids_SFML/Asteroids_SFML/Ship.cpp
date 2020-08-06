#include "Ship.h"
#include <SFML/Graphics.hpp>
#include <iostream>


Ship::Ship() {
    triangle.setPointCount(3);
    triangle.setPoint(0, sf::Vector2f(triangleSize / 2, 0));
    triangle.setPoint(1, sf::Vector2f(triangleSize, triangleSize));
    triangle.setPoint(2, sf::Vector2f(0, triangleSize));
    triangle.setOutlineColor(sf::Color::White);
    triangle.setOutlineThickness(3);
    triangle.setPosition(500, 500);
    triangle.setFillColor(sf::Color::Black);
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

    position.y = position.y + (velocity * deltaTime.asSeconds());
    triangle.setPosition(position.x, position.y);
}

void Ship::GetInput(sf::Time deltaTime) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        isThrusting = true;
    }
    else {
        isThrusting = false;
    }
}