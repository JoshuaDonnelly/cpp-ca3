#ifndef BUG_H
#define BUG_H

#include "Position.h"
#include <list>
#include <string>
#include <fstream>

enum class Direction { North = 1, East = 2, South = 3, West = 4 };

class Bug {
protected:
    int id;
    Position position;
    Direction direction;
    int size;
    bool alive;
    std::list<Position> path;
    int killerId;

public:
    Bug(int id, int x, int y, Direction dir, int size);
    virtual ~Bug() = default;

    // Pure virtual functions
    virtual void move() = 0;
    virtual std::string getType() const = 0;

    // Common methods
    bool isWayBlocked() const;
    void display() const;
    void displayLifeHistory() const;
    void writeLifeHistory(std::ofstream& ofs) const;

    // Getters and setters
    int getId() const { return id; }
    const Position& getPosition() const { return position; }
    Direction getDirection() const { return direction; }
    int getSize() const { return size; }
    bool isAlive() const { return alive; }
    void setDead() { alive = false; }
    const std::list<Position>& getPath() const { return path; }
    int getKillerId() const { return killerId; }
    void setKillerId(int id) { killerId = id; }
    void setSize(int newSize) { size = newSize; }
};

#endif // BUG_H