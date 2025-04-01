//
// Created by joshu on 01/04/2025.
//

#ifndef CRAWLER_H
#define CRAWLER_H
#include <list>

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

    public:
    Crawler(int id, int x, int y, Direction dir, int size);

    void move();
    bool isWayBlocked();
    void display ();
    int getId() const {return id;}
    Position getPosition() const {return position;}
    bool isAlive() const {return alive;}

    void setPosition(int x, int y) { position = Position(x, y); }



};



#endif //CRAWLER_H
