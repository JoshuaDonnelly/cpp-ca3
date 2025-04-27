#include "../include/Bug.h"
#include <iostream>
#include <cstdlib>

Bug::Bug(int id, int x, int y, Direction dir, int size) 
    : id(id), position(x, y), direction(dir), size(size), alive(true), killerId(-1) {
    path.push_back(position);
}

bool Bug::isWayBlocked() const {
    return (position.x == 0 && direction == Direction::West) ||
           (position.x == 9 && direction == Direction::East) ||
           (position.y == 0 && direction == Direction::North) ||
           (position.y == 9 && direction == Direction::South);
}

void Bug::display() const {
    std::cout << "Bug ID: " << id
              << " | Type: " << getType()
              << " | Position: (" << position.x << "," << position.y << ")"
              << " | Direction: " << static_cast<int>(direction)
              << " | Size: " << size
              << " | Alive: " << (alive ? "Yes" : "No") << std::endl;
}

void Bug::displayLifeHistory() const {
    std::cout << id << " " << getType() << " Path: ";

    bool first = true;
    for (const auto& pos : path) {
        if (!first) {
            std::cout << " -> ";
        }
        std::cout << "(" << pos.x << "," << pos.y << ")";
        first = false;
    }

    if (!alive) {
        std::cout << " (Eaten by " << killerId << ")";
    }

    std::cout << std::endl;
}

void Bug::writeLifeHistory(std::ofstream& ofs) const {
    ofs << id << " " << getType() << " path: ";
    for (const auto& pos : path) {
        ofs << "(" << pos.x << ", " << pos.y << ") ";
    }
    if (!alive) {
        ofs << "Eaten by " << killerId;
    }
    ofs << "\n";
}