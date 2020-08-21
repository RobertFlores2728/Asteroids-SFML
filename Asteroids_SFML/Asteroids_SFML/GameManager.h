#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>
#include "Ship.h"
#include "Asteroid.h"

//forward decleration
class Ship;
class Asteroid;
class Bullet;

class GameManager
{
public:
	GameManager();

	

	void SetupGame();
	void RunGame();

	void UpdateShips();

	//asteroid
	void UpdateAsteroids();
	void DrawAsteroids();
	void SpawnAsteroids(int n);

	//bullet
	void UpdateBullets();
	void ShootBullet();
	void DespawnBullet(std::shared_ptr<Bullet> b);
	void RemoveLastBullet();
	void PrintBullets();

	//collision
	void CheckCollisions();
	void CheckShipAsteroidCollision();
	void CheckBulletAsteroidCollision();


	//score
	void SetupScore();
	void DrawScore();


	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<sf::Clock> clock;


	//game object vectors
	std::shared_ptr<Ship> ship;
	std::vector< std::shared_ptr<Ship> > ships;

	std::vector < std::shared_ptr<Bullet> > bullets;

	std::vector< std::shared_ptr<Asteroid> > asteroids;

private:
	//sfml game settings
	
	int FPS = 120;
	
	sf::Time deltaTime;

	sf::Text score;
	sf::Font font;

	bool isPaused = false;

	
};

