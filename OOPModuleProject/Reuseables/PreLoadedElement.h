#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Component.h"

class PreLoadedElement
{
private :
	std::string name;
	std::unique_ptr<sf::Sprite> Sprite;
	bool visible = true;

public :
	PreLoadedElement(std::string newName, sf::Texture& elementTexture, float posX, float posY, float scaleX, float scaleY);
	virtual void Draw(sf::RenderWindow& window);
	std::string getName();
	void setVisible(bool newVisible);
};

