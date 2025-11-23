#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Component.h"

class GameMediator;

class UiElement :
	public Component
{
protected :
	sf::Texture elementTexture;
	std::string name;
	std::unique_ptr<sf::Sprite> Sprite;

public :
	UiElement(std::string newName, std::string elementAssetDirectory, float posX, float posY, float scaleX, float scaleY);
	virtual void Draw(sf::RenderWindow& window) override;
	virtual Response requestData(const std::string& request) override;
	virtual void notify(const std::string& message) override;
	virtual std::string getName();
};

