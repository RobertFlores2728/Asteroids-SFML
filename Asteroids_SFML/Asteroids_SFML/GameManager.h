#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>
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
	void SpawnAsteroids(int n);

	//bullet
	void UpdateBullets();
	void ShootBullet();
	void DespawnBullet(std::shared_ptr<Bullet> b);
	void PrintBullets();

	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<sf::Clock> clock;

	std::shared_ptr<Ship> ship;
	//game object vectors
	std::vector< std::shared_ptr<Ship> > ships;

	std::vector < std::shared_ptr<Bullet> > bullets;

	std::vector< std::shared_ptr<Asteroid> > asteroids;

private:
	//sfml game settings
	
	int FPS = 120;
	
	sf::Time deltaTime;

	

	
};

