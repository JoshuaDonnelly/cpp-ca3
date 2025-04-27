#ifndef CRAWLER_H
#define CRAWLER_H

#include "Bug.h"

class Crawler : public Bug {
public:
    Crawler(int id, int x, int y, Direction dir, int size);

    void move() override;
    std::string getType() const override { return "Crawler"; }
};

#endif // CRAWLER_H