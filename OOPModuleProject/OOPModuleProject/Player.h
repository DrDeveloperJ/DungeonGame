#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <memory>
#include "Component.h"

class Player :
	public Component
{
protected:
	sf::Texture monkTexture;
	std::unique_ptr<sf::Sprite> sprite;

	std::string name;
	std::string description;
	int maxHealth = 15;
	int health = 15;
	int attackPoints = 3;
	bool meditatingState = false;
	std::unordered_map<int, bool> claimedUpgrade;

public:
	Player(std::shared_ptr<GameMediator> gameMediatorPtr);

	virtual Response requestData(const std::string& request) override;
	virtual void notify(const std::string& message) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void setName(std::string newName);
	void setDescription(std::string newDescription);
	std::string getName();
	std::string getDescription();

	void updateDetails(std::string newName, std::string newDesc);
	int getCurrentHealth();
	int getAttackPoints();
	void reduceHealth(int healthReduction);
	void addHealth(int healthAdd);
	void addAttackPts(int attackPtsAdd);
	void alterPosition(float posX, float posY);
	void resetHealth();
	void setMeditating(bool newMeditatingState);
	bool getMeditating();
	bool isHealthFull();
	void addMaxHealth(int addedMaxHealth);
	bool checkClaimedUpgrade(int currIncr);
	void setClaimedUpgrade(int currIncr, bool claimed);
	void resetGameplayAttributes();
};