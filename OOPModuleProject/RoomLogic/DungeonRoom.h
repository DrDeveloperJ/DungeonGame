#pragma once
#include "../Component.h"
#include "../EnemyLogic/Enemy.h"
#include "../Reuseables/Button.h"

class DungeonRoom :
	public Component
{
protected:
	virtual void notify(const std::string& message) = 0;
	virtual Response requestData(const std::string& request) = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;
public:
	virtual void createRoomAssets() = 0;
};
