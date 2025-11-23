#include "UpgradeMaxHealthButton.h"
#include "../../GameMediator.h"

UpgradeMaxHealthButton::UpgradeMaxHealthButton(std::shared_ptr<GameMediator> gameMediatorPtr, std::string newName, std::string buttonAssetDirectory, std::string hoverAssetDirectory, float posX, float posY, float scaleX, float scaleY) : Button(newName, buttonAssetDirectory, hoverAssetDirectory, posX, posY, scaleX, scaleY)
{
	gameMediator = gameMediatorPtr;
}

Response UpgradeMaxHealthButton::requestData(const std::string& request)
{
	Response hi = "hello";
	return hi;
}

void UpgradeMaxHealthButton::notify(const std::string& message)
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
		gameMediator->notifyComponent("Player", "maxHealthUpgrade");
		visible = false;
		gameMediator->notifyComponent("UpgradeAttackButton", "setInvisible");
	}
}

void UpgradeMaxHealthButton::Draw(sf::RenderWindow& window)
{
	if (visible)
	{
		window.draw(*Sprite);
	}
}