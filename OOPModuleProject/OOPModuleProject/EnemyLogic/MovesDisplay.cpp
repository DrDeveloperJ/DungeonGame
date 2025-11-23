#include "MovesDisplay.h"

MovesDisplay::MovesDisplay(std::shared_ptr<GameMediator> gameMediatorPtr, std::string attackSuccessTextureDir, std::string attackFailureTextureDir, std::string guardSuccessTextureDir, std::string guardFailureTextureDir, float playerMovePosX, float playerMovePosY, float enemyMovePosX, float enemyMovePosY, float scaleX, float scaleY) : attackSuccessTexture(loadTexture(attackSuccessTextureDir)), playerMoveSprite(attackSuccessTexture), enemyMoveSprite(attackSuccessTexture)
{
	gameMediator = gameMediatorPtr;

	// Load texture for element
	if (attackSuccessTexture.loadFromFile(attackSuccessTextureDir))
	{
		std::cout << "Loaded attackSuccessTexture" << std::endl;
	}
	else
	{
		throw std::runtime_error("Failed to load attackSuccessTexture!");
	}

	if (attackFailureTexture.loadFromFile(attackFailureTextureDir))
	{
		std::cout << "Loaded attackFailureTexture" << std::endl;
	}
	else
	{
		throw std::runtime_error("Failed to load attackFailureTexture!");
	}

	if (guardSuccessTexture.loadFromFile(guardSuccessTextureDir))
	{
		std::cout << "Loaded guardSuccessTexture" << std::endl;
	}
	else
	{
		throw std::runtime_error("Failed to load guardSuccessTexture!");
	}

	if (guardFailureTexture.loadFromFile(guardFailureTextureDir))
	{
		std::cout << "Loaded guardFailureTexture" << std::endl;
	}
	else
	{
		throw std::runtime_error("Failed to load guardFailureTexture!");
	}

	playerMoveSprite.setPosition({ playerMovePosX, playerMovePosY });
	enemyMoveSprite.setPosition({ enemyMovePosX, enemyMovePosY });
	playerMoveSprite.setScale({ scaleX, scaleY });
	enemyMoveSprite.setScale({ scaleX, scaleY });
}

void MovesDisplay::Draw(sf::RenderWindow& window)
{
	// Draws the moves if visible
	if (visible)
	{
		window.draw(playerMoveSprite);
		window.draw(enemyMoveSprite);
	}
}

Response MovesDisplay::requestData(const std::string& request)
{
	Response hi = "hello";
	return hi;
}

void MovesDisplay::notify(const std::string& message)
{
	if (message == "setVisible")
	{
		visible = true;
	}
	else if (message == "setInvisible")
	{
		visible = false;
	}
	else if (message == "PlayerAttackSuccess")
	{
		displayMovePlayer("AttackSuccess");
	}
	else if (message == "PlayerAttackFail")
	{
		displayMovePlayer("AttackFail");
	}
	else if (message == "PlayerGuardSuccess")
	{
		displayMovePlayer("GuardSuccess");
	}
	else if (message == "PlayerGuardFail")
	{
		displayMovePlayer("GuardFail");
	}
	else if (message == "EnemyAttackSuccess")
	{
		displayMoveEnemy("AttackSuccess");
	}
	else if (message == "EnemyAttackFail")
	{
		displayMoveEnemy("AttackFail");
	}
	else if (message == "EnemyGuardSuccess")
	{
		displayMoveEnemy("GuardSuccess");
	}
	else if (message == "EnemyGuardFail")
	{
		displayMoveEnemy("GuardFail");
	}
}

void MovesDisplay::displayMovePlayer(std::string move)
{
	if (move == "AttackSuccess")
	{
		playerMoveSprite.setTexture(attackSuccessTexture);
	}
	else if (move == "AttackFail")
	{
		playerMoveSprite.setTexture(attackFailureTexture);
	}
	else if (move == "GuardSuccess")
	{
		playerMoveSprite.setTexture(guardSuccessTexture);
	}
	else if (move == "GuardFail")
	{
		playerMoveSprite.setTexture(guardFailureTexture);
	}
}

void MovesDisplay::displayMoveEnemy(std::string move)
{
	if (move == "AttackSuccess")
	{
		enemyMoveSprite.setTexture(attackSuccessTexture);
	}
	else if (move == "AttackFail")
	{
		enemyMoveSprite.setTexture(attackFailureTexture);
	}
	else if (move == "GuardSuccess")
	{
		enemyMoveSprite.setTexture(guardSuccessTexture);
	}
	else if (move == "GuardFail")
	{
		enemyMoveSprite.setTexture(guardFailureTexture);
	}
}