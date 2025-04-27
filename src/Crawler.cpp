#include "../include/Crawler.h"
#include <cstdlib>
#include <ctime>

Crawler::Crawler(int id, int x, int y, Direction dir, int size)
    : Bug(id, x, y, dir, size) {}

void Crawler::move() {
    if (isWayBlocked()) {
        direction = static_cast<Direction>((rand() % 4) + 1);
    }

    switch (direction) {
        case Direction::North: position.y -= (position.y > 0) ? 1 : 0; break;
        case Direction::East:  position.x += (position.x < 9) ? 1 : 0; break;
        case Direction::South: position.y += (position.y < 9) ? 1 : 0; break;
        case Direction::West:  position.x -= (position.x > 0) ? 1 : 0; break;
    }

    path.push_back(position);
}