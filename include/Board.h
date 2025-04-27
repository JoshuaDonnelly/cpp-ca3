#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>
#include "Bug.h"

class Board {
private:
    std::vector<Bug*> bugs;

public:
    Board();
    ~Board();

    void loadBugsFromFile(const std::string& fileName);
    void displayBugs() const;

    Bug* findBug(int id);
    std::vector<Bug*>& getBugs() { return bugs; }
    void tapBoard();
    void displayCells() const;
    void displayLifeHistory() const;
    void writeLifeHistory() const;
    void runSimulation();
};

#endif // BOARD_H