//
// Created by joshu on 27/04/2025.
//
#include "../include/Spider.h"
#include <cstdlib>

Spider::Spider(int id, int x, int y, Direction dir, int size)
    : Bug(id, x, y, dir, size) {}

void Spider::move() {
    if (!isAlive()) return;

    // Diagonal movement based on direction
    switch (direction) {
        case Direction::North:
            position.x = std::min(9, position.x + 1);
        position.y = std::max(0, position.y - 1);
        break;
        case Direction::East:
            position.x = std::min(9, position.x + 1);
        position.y = std::min(9, position.y + 1);
        break;
        case Direction::South:
            position.x = std::max(0, position.x - 1);
        position.y = std::min(9, position.y + 1);
        break;
        case Direction::West:
            position.x = std::max(0, position.x - 1);
        position.y = std::max(0, position.y - 1);
        break;
    }

    // Change direction if at edge
    if (isWayBlocked()) {
        direction = static_cast<Direction>((rand() % 4) + 1);
    }

    path.push_back(position);
}