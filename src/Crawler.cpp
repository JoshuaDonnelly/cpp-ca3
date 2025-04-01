//
// Created by joshu on 01/04/2025.
//

#include "../include/Crawler.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

Crawler::Crawler(int id, int x, int y, Direction dir, int size)
    : id(id), position(x, y), direction(dir), size(size), alive(true) {
    path.push_back(position); // Initial position added to path history
}

void Crawler::move() {
    if (isWayBlocked()) {
        direction = static_cast<Direction>((rand() % 4) + 1); // Pick a new random direction
    }

    switch (direction) {
        case Direction::North: position.y -= (position.y > 0) ? 1 : 0; break;
        case Direction::East:  position.x += (position.x < 9) ? 1 : 0; break;
        case Direction::South: position.y += (position.y < 9) ? 1 : 0; break;
        case Direction::West:  position.x -= (position.x > 0) ? 1 : 0; break;
    }

    path.push_back(position); // Record new position
}

bool Crawler::isWayBlocked() {
    return (position.x == 0 && direction == Direction::West) ||
           (position.x == 9 && direction == Direction::East) ||
           (position.y == 0 && direction == Direction::North) ||
           (position.y == 9 && direction == Direction::South);
}

void Crawler::display() {
    std::cout << "Bug ID: " << id
              << " | Position: (" << position.x << "," << position.y << ")"
              << " | Direction: " << static_cast<int>(direction)
              << " | Size: " << size
              << " | Alive: " << (alive ? "Yes" : "No") << std::endl;
}
