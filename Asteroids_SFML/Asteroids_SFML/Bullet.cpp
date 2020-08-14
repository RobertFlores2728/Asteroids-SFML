#include "Bullet.h"

Bullet::Bullet() {}

Bullet::Bullet(sf::RenderWindow& w, Ship& s) {
    window = &w;
    ship = &s;

    clear = sf::Color(0, 0, 0, 0);

    forwardUnitVector.x = std::cos(ship->shipSprite.getRotation() * 3.141592 / 180.0);
    forwardUnitVector.y = std::sin(ship->shipSprite.getRotation() * 3.141592 / 180.0);

    SetupCircleShape();
    SetupSprite();
}

void Bullet::SetupCircleShape() {
    bulletShape.setRadius(bulletSize);
    bulletShape.setOrigin(bulletSize / 2, bulletSize / 2);
    bulletShape.setPosition(bulletSize/2, bulletSize/2);

    bulletShape.setFillColor(sf::Color::White);

}


void Bullet::SetupSprite() {
    position.x = ship->position.x;
    position.y = ship->position.y;

    bulletTexture.create(bulletSize * 2, bulletSize * 2);
    bulletSprite = sf::Sprite(bulletTexture.getTexture());
    bulletSprite.setPosition(position.x, position.y);
    bulletSprite.setOrigin(bulletSize , bulletSize);
    bulletTexture.clear(clear);
    bulletTexture.draw(bulletShape);
    bulletTexture.display();
}


void Bullet::Draw() {
    window->draw(bulletSprite);
}

void Bullet::Update(sf::Time dt) {
    deltaTime = dt;
    Move();
    CheckIfLifeOver();
}


void Bullet::Move() {
    velocity.x = bulletSpeed * forwardUnitVector.x * deltaTime.asSeconds();
    velocity.y = bulletSpeed * -forwardUnitVector.y * deltaTime.asSeconds();

    position.x += velocity.x * deltaTime.asSeconds();
    position.y -= velocity.y * deltaTime.asSeconds();
    bulletSprite.setPosition(position.x, position.y);
    //std::cout << "Position: " << position.x << " " << position.y << std::endl;

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

bool Bullet::CheckIfLifeOver() {
    if (bulletClock.getElapsedTime().asSeconds() > bulletLife) {
        return true;
    }
    return false;
}
