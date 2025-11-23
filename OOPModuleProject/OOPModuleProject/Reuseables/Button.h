#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Component.h"

class Button :
    public Component
{
protected:
    sf::Texture ButtonTexture;
    sf::Texture OnButtonTexture;
    std::string name;
    std::unique_ptr<sf::Sprite> Sprite;
    int ButtonState = 0;
    virtual Response requestData(const std::string& request) = 0;  // Pure virtual
    virtual void notify(const std::string& message) = 0;           // Pure virtual
    virtual void Draw(sf::RenderWindow& window) = 0;               // Pure virtual

public:
    Button(std::string newName, std::string buttonAssetDirectory, std::string hoverAssetDirectory, float posX, float posY, float scaleX, float scaleY);
    ~Button();
    void disableButton();
    void enableButton();
    std::string getName();
    void checkMouseIsOver(sf::RenderWindow& window);
    void switchState(int state);
    int getState();
};