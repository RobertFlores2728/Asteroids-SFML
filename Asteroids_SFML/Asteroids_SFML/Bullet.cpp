#include "Bullet.h"

Bullet::Bullet() {}

Bullet::Bullet(sf::RenderWindow& w){//, Ship& s) {
    window = &w;
    //ship = &s;

    clear = sf::Color(0, 0, 0, 0);

    SetupCircleShape();
    //SetupSprite();
}

void Bullet::SetupCircleShape() {
    bulletShape.setRadius(bulletSize);
    bulletShape.setOrigin(bulletSize / 2, bulletSize / 2);

    bulletShape.setFillColor(sf::Color::White);

}

/*
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
*/

void Bullet::Draw() {
    window->draw(bulletSprite);
}

void Bullet::Update(sf::Time dt) {
    //Move();
}

/*
void Bullet::Move() {
    velocity.x = bulletSpeed * std::cos(ship->shipSprite.getRotation() * 3.141592 / 180.0) * deltaTime.asSeconds();
    velocity.y = bulletSpeed * std::sin(ship->shipSprite.getRotation() * 3.141592 / 180.0) * deltaTime.asSeconds();

    position.x += velocity.x * deltaTime.asSeconds();
    position.y -= velocity.y * deltaTime.asSeconds();
    bulletSprite.setPosition(position.x, position.y);

    // screen wrapping effect
    if (bulletSprite.getPosition().x > window->getSize().x)
        position.x = 0;
    else if (bulletSprite.getPosition().x < 0)
        position.x = window->getSize().x;

    if (bulletSprite.getPosition().y > window->getSize().y)
        position.y = 0;
    else if (bulletSprite.getPosition().y < 0)
        position.y = window->getSize().y;
}
*/