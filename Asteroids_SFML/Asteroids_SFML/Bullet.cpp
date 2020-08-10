#include "Bullet.h"
#include <SFML/Graphics.hpp>
#include "Ship.h"

Bullet::Bullet() {}

Bullet::Bullet(sf::RenderWindow& w, Ship& s) {
    window = &w;
    ship = &s;

    clear = sf::Color(0, 0, 0, 0);

    SetupCircleShape();
    SetupSprite();
}

void Bullet::SetupCircleShape() {
    bulletShape.setRadius(bulletSize);
    bulletShape.setOrigin(bulletSize / 2, bulletSize / 2);

    bulletShape.setFillColor(sf::Color::White);

}

void Bullet::SetupSprite() {
    position.x = ship->position.x;
    position.y = ship->position.y;

    bulletTexture.create(bulletSize * 2, bulletSize * 2);
    bulletSprite = sf::Sprite(bulletTexture.getTexture());
    bulletSprite.setPosition(position.x, position.y);
    bulletSprite.setOrigin((bulletSize * 2) / 2, (bulletSize * 2) / 2);
    bulletTexture.clear(clear);
    bulletTexture.draw(bulletShape);
    bulletTexture.display();
}

void Bullet::Draw() {
    window->draw(bulletSprite);
}

void Bullet::Update(sf::Time dt) {
    
}