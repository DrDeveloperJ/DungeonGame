#pragma once
#include "DungeonRoom.h"

class TreasureRoom : 
    public DungeonRoom 
{
public:
    TreasureRoom(std::shared_ptr<GameMediator> gameMediatorPtr);

    virtual void notify(const std::string& message) override;
    virtual Response requestData(const std::string& request) override;
    virtual void Draw(sf::RenderWindow& window) override;
    virtual void createRoomAssets() override;
};