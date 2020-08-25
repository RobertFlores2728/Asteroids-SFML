#include "GameManager.h"

GameManager::GameManager() {
    SetupGame();
    SetupScore();
    SetupUI();
}



void GameManager::SetupGame() {
    std::srand((int)std::time(0));

	window.reset(new sf::RenderWindow(sf::VideoMode(1000, 1000), "Asteroids!"));
	window->setFramerateLimit(FPS);

    clock.reset(new sf::Clock());

	ship.reset(new Ship(*this));
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
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::P:
                        //std::cout << "P pressed!" << std::endl;
                        isPaused = !isPaused;
                        break;
                }
            }
        }

        window->clear();

        CheckCollisions();

        UpdateGameObjects();
        DrawGameObjects();

        

        DrawScore();

        window->display();

    }
}


void GameManager::UpdateGameObjects() {
    if (isPaused)
        return;

    UpdateShips();
    UpdateAsteroids();
    UpdateBullets();
}

void GameManager::DrawGameObjects() {
    DrawShips();
    DrawAsteroids();
    DrawBullets();
    DrawUI();
}


//SHIPS

void GameManager::UpdateShips() {
    for (std::shared_ptr<Ship> ship : ships) {

        if (ship == nullptr)
            continue;

        ship->Update(deltaTime);
        
    }
}

void GameManager::DrawShips() {
    for (std::shared_ptr<Ship> ship : ships) {

        if (ship == nullptr)
            continue;

        
        ship->Draw();
    }
}


//ASTEROIDS

void GameManager::UpdateAsteroids() {
    if (asteroids.empty()) {
        SpawnAsteroids(8);
    }

    for (std::shared_ptr<Asteroid> asteroid : asteroids) {

        if (asteroid == nullptr)
            continue;

        
        asteroid->Update(deltaTime);
    }
}

void GameManager::DrawAsteroids() {
    for (std::shared_ptr<Asteroid> asteroid : asteroids) {

        if (asteroid == nullptr)
            continue;

       
        asteroid->Draw();
    }
}


//BULLETS
void GameManager::UpdateBullets() {
    for (std::shared_ptr<Bullet> bullet : bullets) {

        if (bullet == nullptr) // fixed the error!
            continue;


        bullet->Update(deltaTime);

        if (bullet->CheckIfLifeOver()) {
            DespawnBullet(bullet);
            //continue;
        }
    }
}

void GameManager::DrawBullets() {
    for (std::shared_ptr<Bullet> bullet : bullets) {

        if (bullet == nullptr) // fixed the error!
            continue;

        bullet->Draw();
    }
}

void GameManager::ShootBullet() {
    std::shared_ptr<Bullet> b(new Bullet(*this));
    bullets.push_back(b);

    //PrintBullets();
}

void GameManager::DespawnBullet(std::shared_ptr<Bullet> b) {

    if (bullets.empty())
        return;



    for (int i = 0; i < bullets.size(); i++) {
        if (b == bullets.at(i)) {

            //std::cout << "Removing Bullet: " << bullets.at(i) << " at index: " << i << std::endl;
            bullets.erase(bullets.begin() + i);
        }
    }



    //PrintBullets();
}

void GameManager::PrintBullets() {
    //print bullets
    std::cout << "Bullets:" << std::endl;
    for (std::shared_ptr<Bullet> bullet : bullets) {
        if (bullet == nullptr)
            continue;

        std::cout << bullet << std::endl;
    }

    std::cout << std::endl;
}



void GameManager::SpawnAsteroids(int n) {
    
    for (int i = 0; i < n; i++) {


        //position
        sf::Vector2<float> position;
        float positionsDifferenceMagnitude = 0;
        while (positionsDifferenceMagnitude < 600.0f) {
            //position
            position.x = 1 + rand() % (window->getSize().x + 0);
            position.y = 1 + rand() % (window->getSize().y + 0);

            sf::Vector2<float> positionsDifference;
            positionsDifference.x = position.x - ship->position.x;
            positionsDifference.y = position.y - ship->position.y;

            positionsDifferenceMagnitude = std::sqrtf(std::powf(positionsDifference.x, 2) + std::powf(positionsDifference.y, 2));
        }
        //std::cout << "asteroid-ship distance magnitude: " << positionsDifferenceMagnitude << std::endl;


        //direction
        sf::Vector2f forwardUV;
        float angle = 1 + rand() % (358 + 1);
        forwardUV.x = std::cos(angle * (3.141592 / 180.0));
        forwardUV.y = std::sin(angle * (3.141592 / 180.0));



        //speed
        float speed = 1 * 10000.0f;


        //size
        float size = 45 + rand() % (4 + 1);
        //std::cout << "Asteroid size: " << size << std::endl;


        std::shared_ptr<Asteroid> a(new Asteroid(*this, forwardUV, position, speed, size));
        asteroids.push_back(a);
    }   
}

void GameManager::SpawnLittleAsteroids(int n, float parentSize, sf::Vector2f parentAsteroidPos) {
    if (parentSize < 45.0f)
        return;
    
    for (int i = 0; i < n; i++) {
        //direction
        sf::Vector2f forwardUV;
        float angle = 1 + rand() % (358 + 1);
        forwardUV.x = std::cos(angle * (3.141592 / 180.0));
        forwardUV.y = std::sin(angle * (3.141592 / 180.0));



        //speed
        float speed = 2 * 10000.0f;


        //size
        float size = 20 + rand() % (9 + 1);
        //std::cout << "Asteroid size: " << size << std::endl;


        std::shared_ptr<Asteroid> a(new Asteroid(*this, forwardUV, parentAsteroidPos, speed, size));
        asteroids.push_back(a);
    }
}


void GameManager::DespawnAsteroid(std::shared_ptr<Asteroid> a) {

    if (asteroids.empty())
        return;



    for (int i = 0; i < asteroids.size(); i++) {
        if (a == asteroids.at(i)) {
            asteroids.erase(asteroids.begin() + i);
        }
    }
}


void GameManager::PrintAsteroids() {
    //print asteroids
    std::cout << "Asteroids:" << std::endl;
    for (std::shared_ptr<Asteroid> a : asteroids) {
        if (a == nullptr)
            continue;

        std::cout << a << std::endl;
    }

    std::cout << std::endl;
}






//COLLISION
void GameManager::CheckCollisions() {
    CheckShipAsteroidCollision();
    CheckBulletAsteroidCollision();
}

void GameManager::CheckShipAsteroidCollision() {
    for (std::shared_ptr<Asteroid> asteroid : asteroids) {

        if (asteroid == nullptr)
            continue;

        if (Collision::BoundingBoxTest(asteroid->asteroidSprite, ship->shipSprite)) {
            //std::cout << "Collision - Bounding box!" << std::endl;

            if (Collision::PixelPerfectTest(asteroid->asteroidSprite, ship->shipSprite)) {
                //std::cout << "Collision - Pixel perfect!" << std::endl;
                ship->Die();
            }
        }
    }
}

/* this function tricky to implement!
* spawning asteroids could not be done inside of the pixel perfect collision test if statement without a null pointer error occuring
* perhaps the asteroids vector should not be modififed while its being iterated through mid loop
* there are still bugs but are less common now
*/
void GameManager::CheckBulletAsteroidCollision() {
    bool collision = false;
    float aSize = 0.0f;
    sf::Vector2f aPos;
    for (std::shared_ptr<Bullet> bullet : bullets) {

        if (bullet == nullptr)
            continue;

        for (std::shared_ptr<Asteroid> asteroid : asteroids) {

            if (asteroid == nullptr)
                continue;


            if (Collision::BoundingBoxTest(asteroid->asteroidSprite, bullet->bulletSprite)) {
                //std::cout << "Collision - Bounding box!" << std::endl;

                if (Collision::PixelPerfectTest(asteroid->asteroidSprite, bullet->bulletSprite)) {
                    //std::cout << "Collision - Pixel perfect!" << std::endl;
                    DespawnBullet(bullet);
                    collision = true;
                    aSize = asteroid->asteroidSize;
                    aPos = asteroid->position;
                    
                    DespawnAsteroid(asteroid);
                    IncrementScore();
                }
            }
        }
        
    }
    if (collision)
        SpawnLittleAsteroids(2, aSize, aPos);
}



//SCORE
void GameManager::SetupScore() {
    

    font.loadFromFile("res/Boba Panda Font/Boba Panda Font by 7NTypes.otf");

    scoreText.setFont(font);

    sf::Vector2<float> position;
    position.x = window->getSize().x / 2;
    position.y = 0;
    scoreText.setPosition(position);

    scoreText.setString("Score: " + std::to_string(score));
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::White);
    

}

void GameManager::DrawScore() {
    window->draw(scoreText);
}

void GameManager::IncrementScore() {
    score += 100;
    scoreText.setString("Score: " + std::to_string(score));
}




//UI
void GameManager::SetupUI() {
    sf::Vector2f position(250, 250);
    std::shared_ptr<Button> pause(new Button(*this, "Pause", position));
    buttons.push_back(pause);
}

void GameManager::DrawUI() {
    if (isPaused) {
        for (std::shared_ptr<Button> b : buttons) {

            if (b == nullptr)
                continue;


            b->Draw();
        }
    }
}