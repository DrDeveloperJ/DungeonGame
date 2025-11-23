#include "PlayerHealthBar.h"

void PlayerHealthBar::Draw(sf::RenderWindow& window)
{
	if (visible)
	{
		window.draw(*Sprite);
		window.draw(text);
	}
}

PlayerHealthBar::PlayerHealthBar(std::shared_ptr<GameMediator> gameMediatorPtr, std::string newName, std::string barAssetDirectory, float posX, float posY, float scaleX, float scaleY) : font("JdmgtR34raz9.ttf"), text(font, "")
{
	gameMediator = gameMediatorPtr;
	name = newName;

	// Load texture for element
	if (elementTexture.loadFromFile(barAssetDirectory))
	{
		std::cout << "Loaded ValueBar Texture" << std::endl;
		Sprite = std::make_unique<sf::Sprite>(elementTexture);
	}
	else
	{
		throw std::runtime_error("Failed to load ValueBar texture!");
	}

	Sprite->setPosition({ posX, posY });
	Sprite->setScale({ scaleX, scaleY });

	float horizontalAlign = Sprite->getGlobalBounds().size.x;
	text.setPosition({ posX + (horizontalAlign / 2.3f), posY });
	text.setCharacterSize(30);
}

void PlayerHealthBar::setText(std::string newText)
{
	text.setString(newText);
}

std::string PlayerHealthBar::getName()
{
	return name;
}

Response PlayerHealthBar::requestData(const std::string& request)
{
	Response hi = "hello";
	return hi;
}

void PlayerHealthBar::notify(const std::string& message)
{
	if (message == "setVisible")
	{
		if (gameMediator != nullptr)
		{
			visible = true;
			Response newDisplayedHealth = gameMediator->requestData("Player", "Health");
			if (std::holds_alternative<int>(newDisplayedHealth)) {
				setText(std::to_string(std::get<int>(newDisplayedHealth)));
			}
		}
	}
	else if (message == "setInvisible")
	{
		visible = false;
	}
}
