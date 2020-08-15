#include "Bullet.h"

Bullet::Bullet() {}

Bullet::Bullet(GameManager &gameManager) {

    gm = &gameManager;


    clear = sf::Color(0, 0, 0, 0);

    forwardUnitVector.x = std::cos(gm->ship->shipSprite.getRotation() * 3.141592 / 180.0);
    forwardUnitVector.y = std::sin(gm->ship->shipSprite.getRotation() * 3.141592 / 180.0);

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
    position.x = gm->ship->position.x;
    position.y = gm->ship->position.y;

    bulletTexture.create(bulletSize * 2, bulletSize * 2);
    bulletSprite = sf::Sprite(bulletTexture.getTexture());
    bulletSprite.setPosition(position.x, position.y);
    bulletSprite.setOrigin(bulletSize , bulletSize);
    bulletTexture.clear(clear);
    bulletTexture.draw(bulletShape);
    bulletTexture.display();
}


void Bullet::Draw() {
    gm->window->draw(bulletSprite);
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
    if (bulletSprite.getPosition().x > gm->window->getSize().x)
        position.x = 0;
    else if (bulletSprite.getPosition().x < 0)
        position.x = gm->window->getSize().x;

    if (bulletSprite.getPosition().y > gm->window->getSize().y)
        position.y = 0;
    else if (bulletSprite.getPosition().y < 0)
        position.y = gm->window->getSize().y;
}

bool Bullet::CheckIfLifeOver() {
    if (bulletClock.getElapsedTime().asSeconds() > bulletLife) {
        return true;
    }
    return false;
}
