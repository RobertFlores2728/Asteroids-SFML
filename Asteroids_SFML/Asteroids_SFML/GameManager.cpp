#include "GameManager.h"

GameManager::GameManager() {
    SetupGame();
}


void GameManager::SetupGame() {
	window = new sf::RenderWindow(sf::VideoMode(1000, 1000), "Asteroids!");
	window->setFramerateLimit(FPS);

    clock = new sf::Clock();

	ship = new Ship(*window);
	ships.push_back(ship);

    SpawnAsteroids(8);
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

        window->display();

    }
}

void GameManager::UpdateShips() {
    for (Ship* ship : ships) {
        ship->Update(deltaTime);
        ship->Draw();
    }
}

void GameManager::UpdateAsteroids() {
    for (Asteroid* asteroid : asteroids) {
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


        Asteroid* a = new Asteroid(*window, *ship, forwardUV, position, speed);
        asteroids.push_back(a);
    }

    for (Asteroid* asteroid : asteroids) {
        std::cout << "Asteroid: " << asteroid << std::endl;
    }
}
