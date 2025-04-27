#ifndef HOPPER_H
#define HOPPER_H

#include "Bug.h"

class Hopper : public Bug {
private:
    int hopLength;

public:
    Hopper(int id, int x, int y, Direction dir, int size, int hopLength);

    void move() override;
    std::string getType() const override { return "Hopper"; }
    int getHopLength() const { return hopLength; }
};

#endif // HOPPER_H