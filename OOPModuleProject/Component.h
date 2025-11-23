#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Response.h"

class GameMediator; // Forward declaration

class Component {
protected:
    bool visible;
    std::shared_ptr<GameMediator> gameMediator;

public:
    Component();
    virtual ~Component() = default;
    virtual void setVisible(bool newVisible);
    virtual Response requestData(const std::string& request) = 0;  // Pure virtual
    virtual void notify(const std::string& message) = 0;           // Pure virtual
    virtual void Draw(sf::RenderWindow& window) = 0;               // Pure virtual
};

template<typename T>
const T* getResponse(const Response& res) {
    return std::get_if<T>(&res);
}
