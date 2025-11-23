#pragma once
#include "../Button.h"

class TreasureButton :
    public Button
{
public:
    TreasureButton(std::shared_ptr<GameMediator> gameMediatorPtr, std::string newName, std::string buttonAssetDirectory, std::string hoverAssetDirectory, float posX, float posY, float scaleX, float scaleY);
    virtual Response requestData(const std::string& request) override;
    virtual void notify(const std::string& message) override;
    virtual void Draw(sf::RenderWindow& window) override;
};
