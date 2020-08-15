#include "GameManager.h"

GameManager::GameManager() {
    SetupGame();
}


void GameManager::SetupGame() {
	window.reset(new sf::RenderWindow(sf::VideoMode(1000, 1000), "Asteroids!"));
	window->setFramerateLimit(FPS);

    clock.reset(new sf::Clock());

	ship.reset(new Ship(*this));
	ships.push_back(ship);

    //SpawnAsteroids(8);
}

void GameManager::RunGame() {
    while (window->isOpen())
    {
        deltaTime = clock->getElapsedTime();
        clock->restart();


        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        window->clear();

        UpdateShips();
        UpdateAsteroids();
        UpdateBullets();

        window->display();

    }
}

void GameManager::UpdateShips() {
    for (std::shared_ptr<Ship> ship : ships) {
        ship->Update(deltaTime);
        ship->Draw();
    }
}

void GameManager::UpdateAsteroids() {
    for (std::shared_ptr<Asteroid> asteroid : asteroids) {
        asteroid->Update(deltaTime);
        asteroid->Draw();
    }
}

void GameManager::SpawnAsteroids(int n) {
    std::srand((int)std::time(0));
    for (int i = 0; i < n; i++) {
        float asteroidSpeed = 1 * 10000.0f;
        sf::Vector2f forwardUV;

        //direction
        forwardUV.x = std::cos(45 * (3.141592 / 180.0));
        forwardUV.y = std::sin(45 * (3.141592 / 180.0));

        //position
        sf::Vector2<float> position;
        position.x = 1 + rand() % (window->getSize().x + 0);
        position.y = 1 + rand() % (window->getSize().y + 0);


        //speed
        float speed = 1 * 10000.0f;


        std::shared_ptr<Asteroid> a(new Asteroid(*this, forwardUV, position, speed));
        asteroids.push_back(a);
    }

    for (std::shared_ptr<Asteroid> asteroid : asteroids) {
        std::cout << "Asteroid: " << asteroid << std::endl;
    }
}



//bullet
void GameManager::UpdateBullets() {
    for (std::shared_ptr<Bullet> bullet : bullets) {
        bullet->Update(deltaTime);
        bullet->Draw();
        if (bullet->CheckIfLifeOver()) {
            DespawnBullet(bullet);
        }
    }
}


void GameManager::ShootBullet() {
    std::shared_ptr<Bullet> b(new Bullet(*this));
    bullets.push_back(b);

    PrintBullets();
}

void GameManager::DespawnBullet(std::shared_ptr<Bullet> b) {
    for (int i = 0; i < bullets.size(); i++) {
        if (b == bullets.at(i)) {
            std::cout << "Removed Bullet: " << bullets.at(i) << " at index: " << i << std::endl;
            bullets.erase(bullets.begin() + i);
        }
    }

    PrintBullets();
}

void GameManager::PrintBullets() {
    //print bullets
    std::cout << "Bullets:" << std::endl;
    for (std::shared_ptr<Bullet> bullet : bullets) {
        std::cout << bullet << std::endl;
    }

    std::cout << std::endl;
}
