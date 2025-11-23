#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "../GameMediator.h"
#include "../Component.h"

class EnemyHealthBar : public Component
{
protected:
    sf::Texture elementTexture;
    std::string name;
    std::unique_ptr<sf::Sprite> Sprite;

    sf::Font font;
    sf::Text text;
    int value = 0;

public:
    EnemyHealthBar(std::shared_ptr<GameMediator> gameMediatorPtr, std::string newName, std::string barAssetDirectory, float posX, float posY, float scaleX, float scaleY);
    virtual ~EnemyHealthBar() = default;

    virtual void setText(std::string newText);
    virtual std::string getName();

    Response requestData(const std::string& request) override;
    void notify(const std::string& message) override;
    void Draw(sf::RenderWindow& window) override;
};