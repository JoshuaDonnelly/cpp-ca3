//
// Created by joshu on 01/04/2025.
//

#ifndef CRAWLER_H
#define CRAWLER_H
#include <fstream>
#include <list>
#include <queue>
#include "Position.h"


enum class Direction  { North = 1, East, South, West };

class Crawler {
private:
    int id;
    Position position;
    Direction direction;
    int size;
    bool alive;
    std::list<Position> path;
    int killerId = -1;

public:
    Crawler(int id, int x, int y, Direction dir, int size);
    void move();
    void display();
    bool isWayBlocked();
    int getId() const { return id; }
    void recordPosition();
    void displayLifeHistory() const;
    void writeLifeHistory(std::ofstream& ofs) const;
    bool isAlive() const { return alive; }
    void setDead() { alive = false; }

      const std::list<Position>& getPath() const;
    void setKillerId(int id) { killerId = id; }
    int getKillerId() const { return killerId; }
    Position getPosition() const { return position; }
    void setSize(int newSize) { size = newSize; }
    int getSize() const { return size; }
};



#endif //CRAWLER_H
