#include "PreLoadedElement.h"

PreLoadedElement::PreLoadedElement(std::string newName, sf::Texture& elementTexture, float posX, float posY, float scaleX, float scaleY)
{
	Sprite = std::make_unique<sf::Sprite>(elementTexture);
	name = newName;
	Sprite->setPosition({ posX, posY });
	Sprite->setScale({ scaleX, scaleY });
}

void PreLoadedElement::Draw(sf::RenderWindow& window)
{
	if (visible)
	{
		window.draw(*Sprite);
	}
}

std::string PreLoadedElement::getName()
{
	return name;
}

void PreLoadedElement::setVisible(bool newVisible)
{
	visible = newVisible;
}