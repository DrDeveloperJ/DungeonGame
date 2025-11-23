#include "Reuseables/UiElement.h"
#include "Reuseables/Button.h"
#include "Component.h"
#include "Game.h"
#include "GameMediator.h"

void GameMediator::registerComponent(const std::string& name, std::shared_ptr<Component> component) {
	components[name] = component;
	orderedDisplay.push_back(component);
}

Response GameMediator::requestData(const std::string& from, const std::string& request) {
	if (components.find(from) != components.end()) {
		return components[from]->requestData(request);
	}
	return "Component not found";
}

void GameMediator::updateButtonStates()
{
	Response windowResponse = requestData("Game", "RenderWindow");

	if (std::holds_alternative<sf::RenderWindow*>(windowResponse))
	{
		if (std::get<sf::RenderWindow*>(windowResponse))
		{
			sf::RenderWindow* window = std::get<sf::RenderWindow*>(windowResponse);

			for (const auto& componentPair : components)
			{
				if (auto button = std::dynamic_pointer_cast<Button>(componentPair.second)) {
					button->checkMouseIsOver(*window);
				}
			}
		}
	}
}

void GameMediator::drawAll()
{

	Response windowResponse = requestData("Game", "RenderWindow");

	if (std::holds_alternative<sf::RenderWindow*>(windowResponse)) {
		sf::RenderWindow* window = std::get<sf::RenderWindow*>(windowResponse);
		
		for (const auto& component : orderedDisplay)
		{
			component->Draw(*window);
		}
	}
	else {
		std::cerr << "Error: Expected sf::RenderWindow*, but got " << windowResponse.index() << std::endl;
	}
}

void GameMediator::notifyButtonClick()
{
	// Finds which button has been clicked

	for (const auto& componentPair : components)
	{
		if (auto button = std::dynamic_pointer_cast<Button>(componentPair.second)) {
			if (button->getState() == 1) {
				button->switchState(0);
				const std::string& name = button->getName();
				std::cout << "Notifying: " << name << std::endl;
				notifyComponent(name, "Clicked");
				button->switchState(0);
			}
		}
	}
}

void GameMediator::makeAllInvisible()
{
	for (const auto& componentPair : components)
	{
		componentPair.second->setVisible(false);
	}
}

void GameMediator::notifyComponent(const std::string& from, const std::string& message) {
	if (components.find(from) != components.end()) {
		components[from]->notify(message);
	}
}