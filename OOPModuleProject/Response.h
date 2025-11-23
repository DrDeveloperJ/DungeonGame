#pragma once
#include <iostream>
#include "RoomLogic/RoomTypes.h"

using Response = std::variant<
    std::string,
    int,
    float,
    bool, 
    std::vector<float>, 
    sf::RenderWindow*, 
    std::pair<std::pair<RoomType, int>, bool>
>;