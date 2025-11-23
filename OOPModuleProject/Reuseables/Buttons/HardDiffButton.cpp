#include "HardDiffButton.h"
#include "../../GameMediator.h"

HardDiffButton::HardDiffButton(std::shared_ptr<GameMediator> gameMediatorPtr, std::string newName, std::string buttonAssetDirectory, std::string hoverAssetDirectory, float posX, float posY, float scaleX, float scaleY) : Button(newName, buttonAssetDirectory, hoverAssetDirectory, posX, posY, scaleX, scaleY)
{
	gameMediator = gameMediatorPtr;
}

Response HardDiffButton::requestData(const std::string& request)
{
	Response hi = "hello";
	return hi;
}

void HardDiffButton::notify(const std::string& message)
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
	else if (message == "setHardDifficulty")
	{
		gameMediator->notifyComponent("RoomSelector", "setHardDifficulty");
	}
}

void HardDiffButton::Draw(sf::RenderWindow& window)
{
	if (visible)
	{
		window.draw(*Sprite);
	}
}