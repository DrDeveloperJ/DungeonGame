#pragma once
#include "Enemy.h"

class Goblin :
    public Enemy
{
public:
    Goblin(std::shared_ptr<GameMediator> gameMediatorPtr);
    virtual void resetHealth() override;
    virtual int getCurrentHealth() override;
    virtual int getAttackPoints() override;
    virtual void reduceHealth(int healthRemove) override;
    virtual void addHealth(int healthAdd) override;
    virtual void notify(const std::string& message) override;
    virtual Response requestData(const std::string& request) override;
    virtual void Draw(sf::RenderWindow& window) override;
};
