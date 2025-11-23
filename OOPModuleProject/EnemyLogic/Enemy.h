#pragma once
#include "../Component.h"
#include "../Reuseables/Button.h"

class Game;

class Enemy :
	public Component
{
protected:
    int health;
    int attackPoints;
    sf::Texture EnemyTexture;
    std::unique_ptr<sf::Sprite> sprite;

public:
    virtual void resetHealth() = 0;
    virtual int getCurrentHealth() = 0;
    virtual int getAttackPoints() = 0;
    virtual void reduceHealth(int healthRemove) = 0;
    virtual void addHealth(int healthAdd) = 0;
	virtual void notify(const std::string& message) = 0;
	virtual Response requestData(const std::string& request) = 0;
    virtual void Draw(sf::RenderWindow& window) = 0;
};
