#include "CombatMediator.h"
#include "../GameMediator.h"

CombatMediator::CombatMediator(std::shared_ptr<GameMediator> gameMediatorPtr)
{
	gameMediator = gameMediatorPtr;
}

Response CombatMediator::requestData(const std::string& request)
{
	if (request == "inCombat?")
	{
		return inCombat;
	}

	Response hi = "hello";
	return hi;
}

void CombatMediator::notify(const std::string& message)
{
	if (message == "inCombat")
	{
		inCombat = true;
	}
	else if (message == "notInCombat")
	{
		inCombat = false;
	}
	else if (message == "Attack")
	{
		attackEnemy();
	}
	else if (message == "Guard")
	{
		guardEnemy();
	}
	else if (message == "CheckBothHealth")
	{
		checkBothHealth();
	}
}

void CombatMediator::Draw(sf::RenderWindow& window)
{
}

void CombatMediator::checkBothHealth()
{
	Response plyerDeadCheck = gameMediator->requestData("Player", "checkIsDead");

	if (std::holds_alternative<bool>(plyerDeadCheck)) {
		bool playerCheck = std::get<bool>(plyerDeadCheck);
		
		if (playerCheck)
		{
			inCombat = false;
			gameMediator->notifyComponent("RoomSelector", "reset");
			gameMediator->notifyComponent("Game", "HomePage");
			gameMediator->notifyComponent("Enemy", "resetHealth");
			gameMediator->notifyComponent("Player", "resetHealth");
			gameMediator->notifyComponent("Player", "resetGameplayAttributes");
			gameMediator->notifyComponent("ExploredDungeonsDisplay", "reset");
			gameMediator->notifyComponent("ExploredDungeonsDisplay", "setInvisible");
		}
		else
		{
			Response enemyDeadCheck = gameMediator->requestData("Enemy", "checkIsDead");

			if (std::holds_alternative<bool>(enemyDeadCheck)) {
				bool enemyCheck = std::get<bool>(enemyDeadCheck);

				if (enemyCheck)
				{
					inCombat = false;
					gameMediator->notifyComponent("Enemy", "setInvisible");
					gameMediator->notifyComponent("EnemyHealthBar", "setInvisible");
					gameMediator->notifyComponent("AttackButton", "setInvisible");
					gameMediator->notifyComponent("GuardButton", "setInvisible");
					gameMediator->notifyComponent("ForwardButton", "setVisible");
					gameMediator->notifyComponent("MovesDisplay", "setInvisible");

					Response firstRoom = gameMediator->requestData("RoomSelector", "IsFirstRoom?");

					if (std::holds_alternative<bool>(firstRoom)) {
						bool first = std::get<bool>(firstRoom);
						if (first)
						{
							gameMediator->notifyComponent("BackButton", "setInvisible");
						}
						else
						{
							gameMediator->notifyComponent("BackButton", "setVisible");
						}
					}
					else {
						std::cerr << "Error: Expected firstRoom, but got " << firstRoom.index() << std::endl;
					}

					gameMediator->notifyComponent("Enemy", "resetHealth");
				}
			}
			else {
				std::cerr << "Error: Expected enemyDeadCheck, but got " << enemyDeadCheck.index() << std::endl;
			}
			
		}
	}
	else {
		std::cerr << "Error: Expected plyerDeadCheck, but got " << plyerDeadCheck.index() << std::endl;
	}
}

void CombatMediator::attackEnemy()
{
	Response enemyDeadCheck = gameMediator->requestData("Enemy", "checkIsDead");

	if (std::holds_alternative<bool>(enemyDeadCheck)) {
		bool enemyCheck = std::get<bool>(enemyDeadCheck);

		if (!enemyCheck)
		{
			gameMediator->notifyComponent("MovesDisplay", "setVisible");

			int chanceBasedAttackChoice = rand() % 2;

			if (chanceBasedAttackChoice)
			{
				gameMediator->notifyComponent("MovesDisplay", "PlayerAttackSuccess");
				gameMediator->notifyComponent("Enemy", "getAttacked");
			}
			else
			{
				gameMediator->notifyComponent("MovesDisplay", "PlayerAttackFail");
			}

			int enemyChoice = rand() % 2;
			if (enemyChoice)
			{
				int enemyChanceBasedChoice = rand() % 2;
				if (enemyChanceBasedChoice)
				{
					gameMediator->notifyComponent("MovesDisplay", "EnemyGuardSuccess");
					gameMediator->notifyComponent("Enemy", "Guard");
				}
				else
				{
					gameMediator->notifyComponent("MovesDisplay", "EnemyGuardFail");
				}
			}
			else
			{
				int enemyChanceBasedChoice = rand() % 2;
				if (enemyChanceBasedChoice)
				{
					gameMediator->notifyComponent("MovesDisplay", "EnemyAttackSuccess");
					gameMediator->notifyComponent("Player", "getAttacked");
				}
				else
				{
					gameMediator->notifyComponent("MovesDisplay", "EnemyAttackFail");
				}
			}
		}
	}
	else {
		std::cerr << "Error: Expected enemyDeadCheck, but got " << enemyDeadCheck.index() << std::endl;
	}
}

void CombatMediator::guardEnemy()
{
	Response enemyDeadCheck = gameMediator->requestData("Enemy", "checkIsDead");

	if (std::holds_alternative<bool>(enemyDeadCheck)) {
		bool enemyCheck = std::get<bool>(enemyDeadCheck);
		if (!enemyCheck)
		{
			gameMediator->notifyComponent("MovesDisplay", "setVisible");

			int enemyChoice = rand() % 2;
			if (enemyChoice)
			{
				int chanceBasedAttackChoice = rand() % 2;
				if (chanceBasedAttackChoice)
				{
					gameMediator->notifyComponent("MovesDisplay", "PlayerGuardSuccess");
					gameMediator->notifyComponent("Player", "Guard");
				}
				else
				{
					gameMediator->notifyComponent("MovesDisplay", "PlayerGuardFail");
				}

				int enemyChanceBasedChoice = rand() % 2;
				if (enemyChanceBasedChoice)
				{
					gameMediator->notifyComponent("MovesDisplay", "EnemyGuardSuccess");
					gameMediator->notifyComponent("Enemy", "Guard");
				}
				else
				{
					gameMediator->notifyComponent("MovesDisplay", "EnemyGuardFail");
				}
			}
			else
			{
				int enemyChanceBasedChoice = rand() % 2;
				if (enemyChanceBasedChoice)
				{
					gameMediator->notifyComponent("MovesDisplay", "EnemyAttackSuccess");
					gameMediator->notifyComponent("Player", "getAttacked");
				}
				else
				{
					gameMediator->notifyComponent("MovesDisplay", "EnemyAttackFail");
				}
			}
		}
	}
}