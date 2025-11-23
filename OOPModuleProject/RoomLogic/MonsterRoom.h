#pragma once
#include "DungeonRoom.h"
#include "../EnemyLogic/EnemyTypes.h"
#include "../EnemyLogic/Enemy.h"
#include "../EnemyLogic/Goblin.h"

class MonsterRoom :
    public DungeonRoom
{
public:
	MonsterRoom(std::shared_ptr<GameMediator> gameMediatorPtr);
	virtual void notify(const std::string& message) override;
	virtual Response requestData(const std::string& request) override;
	virtual void Draw(sf::RenderWindow& window) override;
	virtual void createRoomAssets() override;
};
