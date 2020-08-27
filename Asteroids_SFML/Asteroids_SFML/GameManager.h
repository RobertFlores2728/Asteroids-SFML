#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>
#include "Ship.h"
#include "Asteroid.h"
#include "Button.h"

//forward decleration
class Ship;
class Asteroid;
class Bullet;
class Button;

class GameManager
{
public:
	GameManager();

	

	void SetupGame();
	void RunGame();


	void UpdateGameObjects();
	void DrawGameObjects();

	void PauseGame();
	void QuitGame();

	//ships
	void UpdateShips();
	void DrawShips();

	//asteroids
	void UpdateAsteroids();
	void DrawAsteroids();
	void SpawnAsteroids(int n);
	void DespawnAsteroid(std::shared_ptr<Asteroid> a);
	void SpawnLittleAsteroids(int n, float parentSize, sf::Vector2f parentAsteroidPos);
	void PrintAsteroids();

	//bullets
	void UpdateBullets();
	void DrawBullets();
	void ShootBullet();
	void DespawnBullet(std::shared_ptr<Bullet> b);
	void PrintBullets();

	//collision
	void CheckCollisions();
	void CheckShipAsteroidCollision();
	void CheckBulletAsteroidCollision();


	//score
	void SetupScore();
	void DrawScore();
	void IncrementScore();

	//ui
	void SetupUI();
	void UpdateUI();
	void DrawUI();


	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<sf::Clock> clock;


	//game object vectors
	std::shared_ptr<Ship> ship;
	std::vector< std::shared_ptr<Ship> > ships;

	std::vector < std::shared_ptr<Bullet> > bullets;

	std::vector< std::shared_ptr<Asteroid> > asteroids;


	std::vector < std::shared_ptr<Button> > buttons;

private:
	//sfml game settings
	
	int FPS = 120;
	
	sf::Time deltaTime;

	sf::Text scoreText;
	sf::Font font;

	bool isPaused = false;

	int score = 0;
};

