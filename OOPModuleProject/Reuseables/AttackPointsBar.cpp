#include "AttackPointsBar.h"
#include "../GameMediator.h"

void AttackPointsBar::Draw(sf::RenderWindow& window)
{
	if (visible)
	{
		window.draw(*Sprite);
		window.draw(text);
	}
}

AttackPointsBar::AttackPointsBar(std::shared_ptr<GameMediator> gameMediatorPtr, std::string newName, std::string barAssetDirectory, float posX, float posY, float scaleX, float scaleY) : font("JdmgtR34raz9.ttf"), text(font, "")
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
		throw std::runtime_error("Failed to load Element texture!");
	}

	Sprite->setPosition({ posX, posY });
	Sprite->setScale({ scaleX, scaleY });

	float horizontalAlign = Sprite->getGlobalBounds().size.x;
	text.setPosition({ posX + (horizontalAlign / 2.3f), posY });
	text.setCharacterSize(30);
}

void AttackPointsBar::setText(std::string newText)
{
	text.setString(newText);
}

std::string AttackPointsBar::getName()
{
	return name;
}

Response AttackPointsBar::requestData(const std::string& request)
{
	Response hi = "hello";
	return hi;
}

void AttackPointsBar::notify(const std::string& message)
{
	if (message == "setVisible")
	{
		if (gameMediator != nullptr)
		{
			visible = true;
			Response newDisplayedAttackPoints = gameMediator->requestData("Player", "AttackPoints");
			if (std::holds_alternative<int>(newDisplayedAttackPoints)) {
				setText(std::to_string(std::get<int>(newDisplayedAttackPoints)));
			}
		}
	}
	else if (message == "setInvisible")
	{
		visible = false;
	}
}
