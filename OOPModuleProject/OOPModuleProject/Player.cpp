#include "Player.h"
#include "GameMediator.h"

Player::Player(std::shared_ptr<GameMediator> gameMediatorPtr)
{
	gameMediator = gameMediatorPtr;

	if (monkTexture.loadFromFile("Assets/Monk.png"))
	{
		sprite = std::make_unique<sf::Sprite>(monkTexture);
	}
	else
	{
		throw std::runtime_error("Failed to load Monk texture!");
	}

	sprite->setTexture(monkTexture);
	sprite->setPosition({ 200.0f, 480.0f });

	name = "Monk";
	description = "I'm amazing and on a mission.";
}

Response Player::requestData(const std::string& request)
{
	if (request == "ClaimedUpgrade?")
	{
		Response currentDungeonIncrement = gameMediator->requestData("RoomSelector", "CurrentDungeonIncrement");

		if (std::holds_alternative<int>(currentDungeonIncrement)) {
			int currDungeon = std::get<int>(currentDungeonIncrement);

			return claimedUpgrade[currDungeon];
		}
		else {
			std::cerr << "Error: Expected currentDungeonIncrement, but got " << currentDungeonIncrement.index() << std::endl;
		}
	}
	else if (request == "Health")
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
	else if (request == "Meditating?")
	{
		return meditatingState;
	}
	else if (request == "PlayerName")
	{
		return name;
	}
	else if (request == "PlayerDescription")
	{
		return description;
	}

	Response hi = "Hello";
	return hi;
}

void Player::notify(const std::string& message)
{
	if (message == "setVisible")
	{
		std::cout << "hi";
		visible = true;
	}
	else if (message == "setInvisible")
	{
		visible = false;
	}
	else if (message == "setPositionDefault")
	{
		alterPosition(200.0f, 480.0f);
	}
	else if (message == "ChangeDescription")
	{
		Response textInputResponse = gameMediator->requestData("TextInput", "getText");
		if (std::holds_alternative<std::string>(textInputResponse)) {
			std::string textInput = std::get<std::string>(textInputResponse);
			if (!textInput.empty()) {
				setDescription(textInput);
				gameMediator->notifyComponent("DescriptionDisplay", textInput);
				gameMediator->notifyComponent("Game", "Customize");
			}
			else
			{
				gameMediator->notifyComponent("Game", "Customize");
			}
		}
		else {
			std::cerr << "Error: Expected textInputResponse, but got " << textInputResponse.index() << std::endl;
		}
	}
	else if (message == "ChangeName")
	{
		Response textInputResponse = gameMediator->requestData("TextInput", "getText");
		if (std::holds_alternative<std::string>(textInputResponse)) {
			std::string textInput = std::get<std::string>(textInputResponse);
			if (!textInput.empty()) {
				setName(textInput);
				gameMediator->notifyComponent("NameDisplay", textInput);
				gameMediator->notifyComponent("Game", "Customize");
			}
			else
			{
				gameMediator->notifyComponent("Game", "Customize");
			}
		}
		else {
			std::cerr << "Error: Expected textInputResponse, but got " << textInputResponse.index() << std::endl;
		}
	}
	else if (message == "maxHealthUpgrade")
	{
		Response currentDungeonIncrement = gameMediator->requestData("RoomSelector", "CurrentDungeonIncrement");

		if (std::holds_alternative<int>(currentDungeonIncrement)) {
			int currDungeon = std::get<int>(currentDungeonIncrement);

			claimedUpgrade[currDungeon] = true;
			std::cout << "Claimed Upgrade: " << claimedUpgrade[currDungeon] << std::endl;
		}
		else {
			std::cerr << "Error: Expected currentDungeonIncrement, but got " << currentDungeonIncrement.index() << std::endl;
		}

		addMaxHealth(5);
	}
	else if (message == "attackPointsUpgrade")
	{
		Response currentDungeonIncrement = gameMediator->requestData("RoomSelector", "CurrentDungeonIncrement");

		if (std::holds_alternative<int>(currentDungeonIncrement)) {
			int currDungeon = std::get<int>(currentDungeonIncrement);

			claimedUpgrade[currDungeon] = true;
			std::cout << "Claimed Upgrade: " << claimedUpgrade[currDungeon] << std::endl;
		}
		else {
			std::cerr << "Error: Expected currentDungeonIncrement, but got " << currentDungeonIncrement.index() << std::endl;
		}

		addAttackPts(2);
	}
	else if (message == "Meditate")
	{
		if (health < maxHealth)
		{
			meditatingState = true;
		}
	}
	else if (message == "checkMeditating")
	{
		if (meditatingState)
		{
			if (health < maxHealth)
			{
				addHealth(1);
				std::cout << "Meditating" << std::endl;
			}
			else
			{
				meditatingState = false;
			}
		}
	}
	else if (message == "Guard")
	{
		addHealth(1);
	}
	else if (message == "getAttacked")
	{
		Response attackPoints = gameMediator->requestData("Enemy", "AttackPoints");
		if (std::holds_alternative<int>(attackPoints)) {
			int attackPts = std::get<int>(attackPoints);
			reduceHealth(attackPts);
		}
		else {
			std::cerr << "Error: Expected attackPoints, but got " << attackPoints.index() << std::endl;
		}
	}
	else if (message == "resetHealth")
	{
		resetHealth();
	}
	else if (message == "resetGameplayAttributes")
	{
		resetGameplayAttributes();
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	if (visible)
	{
		window.draw(*sprite);
	}
}

std::string Player::getName()
{
	return name;
}

void Player::setName(std::string newName)
{
	name = newName;
}

void Player::setDescription(std::string newDescription)
{
	description = newDescription;
}

std::string Player::getDescription()
{
	return description;
}

void Player::updateDetails(std::string newName, std::string newDesc)
{
	name = newName;
	description = newDesc;
}

int Player::getCurrentHealth()
{
	return health;
}

int Player::getAttackPoints()
{
	return attackPoints;
}

void Player::reduceHealth(int healthReduction)
{
	health = health - healthReduction;
}

void Player::addHealth(int healthAdd)
{
	health += healthAdd;
}

void Player::addAttackPts(int attackPtsAdd)
{
	attackPoints += attackPtsAdd;
}

void Player::alterPosition(float posX, float posY)
{
	sprite->setPosition({ posX, posY });
}

void Player::resetHealth()
{
	health = 15;
}

void Player::setMeditating(bool newMeditatingState)
{
	meditatingState = newMeditatingState;
}

bool Player::getMeditating()
{
	return meditatingState;
}

bool Player::isHealthFull()
{
	return (health >= maxHealth);
}

void Player::addMaxHealth(int addedMaxHealth)
{
	maxHealth += addedMaxHealth;
}

bool Player::checkClaimedUpgrade(int currIncr)
{
	return claimedUpgrade[currIncr];
}

void Player::setClaimedUpgrade(int currIncr, bool claimed)
{
	claimedUpgrade[currIncr] = claimed;
}

void Player::resetGameplayAttributes()
{
	maxHealth = 15;
	health = 15;
	attackPoints = 3;
	std::unordered_map<int, bool> resetClaimedUpgrade;
	claimedUpgrade = resetClaimedUpgrade;
}
