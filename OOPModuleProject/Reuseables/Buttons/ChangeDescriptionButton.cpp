#include "ChangeDescriptionButton.h"
#include "../../GameMediator.h"

ChangeDescriptionButton::ChangeDescriptionButton(std::shared_ptr<GameMediator> gameMediatorPtr, std::string newName, std::string buttonAssetDirectory, std::string hoverAssetDirectory, float posX, float posY, float scaleX, float scaleY) : Button(newName, buttonAssetDirectory, hoverAssetDirectory, posX, posY, scaleX, scaleY)
{
	gameMediator = gameMediatorPtr;
}

Response ChangeDescriptionButton::requestData(const std::string& request)
{
	Response hi = "hello";
	return hi;
}

void ChangeDescriptionButton::notify(const std::string& message)
{
	ButtonState = 0;
	if (message == "setVisible")
	{
		visible = true;
	}
	else if (message == "setInvisible")
	{
		visible = false;
	}
	else if (message == "Clicked")
	{
		gameMediator->notifyComponent("Player", "ChangeDescription");
	}
}

void ChangeDescriptionButton::Draw(sf::RenderWindow& window)
{
	if (visible)
	{
		window.draw(*Sprite);
	}
}
