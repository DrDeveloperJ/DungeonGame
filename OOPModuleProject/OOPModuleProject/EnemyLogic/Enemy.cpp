#include "Enemy.h"
#include "../Game.h"

void Enemy::resetHealth()
{
}

int Enemy::getCurrentHealth()
{
    return health;
}

int Enemy::getAttackPoints()
{
    return attackPoints;
}

void Enemy::reduceHealth(int healthRemove)
{
    health = health - healthRemove;
}

void Enemy::addHealth(int healthAdd)
{
    health = health + healthAdd;
}

void Enemy::Draw(sf::RenderWindow& window)
{
    if (visible)
    {
        window.draw(*sprite);
    }
}
