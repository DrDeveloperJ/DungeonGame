#pragma once
#include <iostream>
#include "../Component.h"
#include "Enemy.h"
#include "../Player.h"

class CombatMediator :
	public Component
{
protected:
	bool inCombat = false;

public:
	CombatMediator(std::shared_ptr<GameMediator> gameMediatorPtr);
	virtual Response requestData(const std::string& request) override;
	virtual void notify(const std::string& message) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void checkBothHealth();
	void attackEnemy();
	void guardEnemy();
};