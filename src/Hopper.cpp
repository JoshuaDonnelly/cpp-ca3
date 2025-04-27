#include "../include/Hopper.h"
#include <cstdlib>
#include <ctime>

Hopper::Hopper(int id, int x, int y, Direction dir, int size, int hopLength)
    : Bug(id, x, y, dir, size), hopLength(hopLength) {}

void Hopper::move() {

    if (!isAlive()) return;

    bool moved = false;
    int attempts = 0;
    int originalX = position.x;
    int originalY = position.y;

    while (!moved && attempts < 4) {
        int newX = position.x;
        int newY = position.y;

        // Calculate potential new position
        switch (direction) {
            case Direction::North: newY = position.y - hopLength; break;
            case Direction::East:  newX = position.x + hopLength; break;
            case Direction::South: newY = position.y + hopLength; break;
            case Direction::West:  newX = position.x - hopLength; break;
        }

        // Check if new position is valid
        if (newX >= 0 && newX < 10 && newY >= 0 && newY < 10) {
            // Full hop possible
            position.x = newX;
            position.y = newY;
            moved = true;
        } else {
            // Partial hop possible
            if (direction == Direction::North) {
                position.y = std::max(0, position.y - hopLength);
            } else if (direction == Direction::East) {
                position.x = std::min(9, position.x + hopLength);
            } else if (direction == Direction::South) {
                position.y = std::min(9, position.y + hopLength);
            } else if (direction == Direction::West) {
                position.x = std::max(0, position.x - hopLength);
            }

            // Check if we actually moved
            if (position.x != originalX || position.y != originalY) {
                moved = true;
            } else {
                // Change direction if couldn't move
                direction = static_cast<Direction>((rand() % 4) + 1);
                attempts++;
            }
        }
    }

    // Record the new position in path history
    path.push_back(position);
}