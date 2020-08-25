#include "Button.h"

Button::Button(GameManager& gameManager, std::string text, sf::Vector2f pos) {
    
    gm = &gameManager;

    position = pos;
    size = sf::Vector2f(200, 100);

    SetupRectangleShape();
	SetupSprite(text, position);

}

void Button::SetupRectangleShape() {
    
    rectangleShape.setSize(size);
    rectangleShape.setPosition(outlineThickness, outlineThickness);
    rectangleShape.setOutlineColor(sf::Color::White);
    rectangleShape.setOutlineThickness(outlineThickness);
    rectangleShape.setFillColor(sf::Color::Blue);
}

void Button::SetupSprite(std::string text, sf::Vector2f position) {

    buttonTexture.create(size.x + outlineThickness*2, size.y + outlineThickness*2);
    buttonSprite = sf::Sprite(buttonTexture.getTexture());
    buttonSprite.setPosition(position);
    buttonTexture.clear(sf::Color::Black);
    buttonTexture.draw(rectangleShape);
    buttonTexture.display();

}

void Button::SetupText() {
    font.loadFromFile("res/Boba Panda Font/Boba Panda Font by 7NTypes.otf");

    buttonText.setFont(font);

    sf::Vector2<float> position;
    position.x = window->getSize().x / 2;
    position.y = 0;
    scoreText.setPosition(position);

    scoreText.setString("Score: " + std::to_string(score));
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::White);
}

void Button::Draw() {
    //gm->window->draw(rectangleShape);
    gm->window->draw(buttonSprite);
}

void Button::Update() {
    //check for mouse hovering, click, etc.
}