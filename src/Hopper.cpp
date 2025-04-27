#include "../include/Hopper.h"
#include <cstdlib>
#include <ctime>

Hopper::Hopper(int id, int x, int y, Direction dir, int size, int hopLength)
    : Bug(id, x, y, dir, size), hopLength(hopLength) {}

void Hopper::move() {
    int newX = position.x;
    int newY = position.y;
    int attemptedHops = 0;
    bool moved = false;

    while (!moved && attemptedHops < 4) {
        switch (direction) {
            case Direction::North:
                newY = position.y - hopLength;
            if (newY < 0) newY = 0;
            break;
            case Direction::East:
                newX = position.x + hopLength;
            if (newX > 9) newX = 9;
            break;
            case Direction::South:
                newY = position.y + hopLength;
            if (newY > 9) newY = 9;
            break;
            case Direction::West:
                newX = position.x - hopLength;
            if (newX < 0) newX = 0;
            break;
        }

        if (!(newX == position.x && newY == position.y)) {
            position.x = newX;
            position.y = newY;
            moved = true;
        } else {
            direction = static_cast<Direction>((rand() % 4) + 1);
            attemptedHops++;
        }
    }

    path.push_back(position);
}