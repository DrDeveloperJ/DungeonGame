#pragma once
#include <unordered_map>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "Response.h"

class Component; // Forward declaration

class GameMediator {
private:
	std::unordered_map<std::string, std::shared_ptr<Component>> components;
	std::vector<std::shared_ptr<Component>> orderedDisplay; // Necessary to ensure Components are drawn in correct order

public:
	void registerComponent(const std::string& name, std::shared_ptr<Component> component);

	void updateButtonStates();
	void drawAll();
	void notifyButtonClick();
	void makeAllInvisible();

	Response requestData(const std::string& from, const std::string& request);
	void notifyComponent(const std::string& from, const std::string& message);
};