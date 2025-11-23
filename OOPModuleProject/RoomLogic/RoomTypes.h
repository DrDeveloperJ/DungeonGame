#pragma once
#include <string>
#include <ostream>

enum class RoomType {
    MonsterRoom,
    TreasureRoom,
    UpgradeRoom,
    EmptyRoom
};

// Function to convert RoomType to a string
inline std::string toString(RoomType type) {
    switch (type) {
    case RoomType::MonsterRoom: return "MonsterRoom";
    case RoomType::TreasureRoom: return "TreasureRoom";
    case RoomType::UpgradeRoom: return "UpgradeRoom";
    case RoomType::EmptyRoom: return "EmptyRoom";
    default: return "UnknownRoom";
    }
}

// Overloads the << operator for RoomType
inline std::ostream& operator<<(std::ostream& os, RoomType type) {
    return os << toString(type);
}