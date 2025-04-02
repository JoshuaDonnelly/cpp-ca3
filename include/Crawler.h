//
// Created by joshu on 01/04/2025.
//

#ifndef CRAWLER_H
#define CRAWLER_H
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
    std::vector<Position> path;

public:
    Crawler(int id, int x, int y, Direction dir, int size);
    void move();
    void display();
    bool isWayBlocked();
    int getId() const { return id; }  // New method to get the ID
};



#endif //CRAWLER_H
