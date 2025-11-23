#pragma once
#include "DungeonRoom.h"

class UpgradeRoom :
    public DungeonRoom
{
public:
	UpgradeRoom(std::shared_ptr<GameMediator> gameMediatorPtr);
	virtual void notify(const std::string& message) override;
	virtual Response requestData(const std::string& request) override;
	virtual void Draw(sf::RenderWindow& window) override;
	virtual void createRoomAssets() override;
};