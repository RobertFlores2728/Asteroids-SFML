#pragma once

#include "main.h"

class GameManager;



class Button
{
private:
	GameManager* gm;


public:
	sf::RectangleShape rectangleShape;
	sf::Sprite buttonSprite;
	sf::RenderTexture buttonTexture;

	sf::Vector2<float> position;
	sf::Vector2<float> size;

	float outlineThickness = 5.0f;

	sf::Text buttonText;
	std::string text;
	sf::Font font;

	sf::Mouse mouse;
	bool mouseOver = false;


	Button() = delete;

	Button(GameManager& gameManager, std::string text, sf::Vector2f position);

	void SetupRectangleShape();
	void SetupSprite();
	void SetupText();


	void Draw();
	void Update();

	void CheckMouseHover();
	void CheckMouseInput();

	void RunFunction();
};

