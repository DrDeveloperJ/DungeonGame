#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Component.h"

class MovesDisplay :
	public Component
{
private:
	sf::Texture attackSuccessTexture;
	sf::Texture attackFailureTexture;
	sf::Texture guardSuccessTexture;
	sf::Texture guardFailureTexture;
	sf::Sprite playerMoveSprite;
	sf::Sprite enemyMoveSprite;

public:
	MovesDisplay(std::shared_ptr<GameMediator> gameMediatorPtr, std::string attackSuccessTextureDir, std::string attackFailureTextureDir, std::string guardSuccessTextureDir, std::string guardFailureTextureDir, float playerMovePosX, float playerMovePosY, float enemyMovePosX, float enemyMovePosY, float scaleX, float scaleY);
	
	virtual void Draw(sf::RenderWindow& window) override;
	virtual Response requestData(const std::string& request) override;
	virtual void notify(const std::string& message) override;
	
	void displayMovePlayer(std::string move);
	void displayMoveEnemy(std::string move);

	static sf::Texture loadTexture(const std::string& path) {
		sf::Texture texture;
		if (!texture.loadFromFile(path)) {
			throw std::runtime_error("Failed to load texture");
		}
		return texture;
	}
};

