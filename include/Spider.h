//
// Created by joshu on 27/04/2025.
//

#ifndef SPIDER_H
#define SPIDER_H

#include "Bug.h"

class Spider : public Bug {
public:
    Spider(int id, int x, int y, Direction dir, int size);
    void move() override;
    std::string getType() const override { return "Spider"; }
};

#endif //SPIDER_H
