#include "Goblin.h"
#include "../Game.h"

Goblin::Goblin(std::shared_ptr<GameMediator> gameMediatorPtr)
{
	gameMediator = gameMediatorPtr;

	if (EnemyTexture.loadFromFile("Assets/Goblin.png"))
	{
		sprite = std::make_unique<sf::Sprite>(EnemyTexture);
	}
	else
	{
		throw std::runtime_error("Failed to load Goblin texture!");
	}

	sprite->setTexture(EnemyTexture);
	sprite->setPosition({ 750.0f, 480.0f });

	health = 10;
	attackPoints = 2;
}

void Goblin::resetHealth()
{
	health = 10;
}

int Goblin::getCurrentHealth()
{
	return health;
}

int Goblin::getAttackPoints()
{
	return attackPoints;
}

void Goblin::reduceHealth(int healthRemove)
{
	health = health - healthRemove;
}

void Goblin::addHealth(int healthAdd)
{
	health = health + healthAdd;
}

void Goblin::notify(const std::string& message)
{
	if (message == "setVisible")
	{
		visible = true;
	}
	else if (message == "setInvisible")
	{
		visible = false;
	}
	else if (message == "resetHealth")
	{
		resetHealth();
	}
	else if (message == "Guard")
	{
		addHealth(1);
	}
	else if (message == "getAttacked")
	{
		Response attackPoints = gameMediator->requestData("Player", "AttackPoints");
		if (std::holds_alternative<int>(attackPoints)) {
			int attackPts = std::get<int>(attackPoints);
			reduceHealth(attackPts);
		}
		else {
			std::cerr << "Error: Expected attackPoints, but got " << attackPoints.index() << std::endl;
		}
	}
}

Response Goblin::requestData(const std::string& request)
{
	if (request == "Health")
	{
		return health;
	}
	else if (request == "AttackPoints")
	{
		return attackPoints;
	}
	else if (request == "checkIsDead")
	{
		if (health <= 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	Response hi = "Hello";
	return hi;
}

void Goblin::Draw(sf::RenderWindow& window)
{
	if (visible)
	{
		window.draw(*sprite);
	}
}
