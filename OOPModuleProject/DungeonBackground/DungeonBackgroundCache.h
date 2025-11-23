#pragma once
#include "../Reuseables/UiElement.h"
#include "../Component.h"
#include "../Reuseables/PreLoadedElement.h"

class DungeonBackgroundCache :
	public Component
{
protected:
	std::vector<std::shared_ptr<PreLoadedElement>> backgrounds;
	int currentBackgroundIndex = 0;

public:
	DungeonBackgroundCache(std::shared_ptr<GameMediator> gameMediatorPtr);

	virtual Response requestData(const std::string& request) override;
	virtual void notify(const std::string& message) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void addBackground(std::shared_ptr<PreLoadedElement> background);
	int getDungeonBgCount();
};

