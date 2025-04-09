//
// Created by joshu on 01/04/2025.
//

#ifndef BOARD_H
#define BOARD_H
#include <string>
#include <vector>

#include "Crawler.h"


class Board {
private:
    std::vector<Crawler*> crawlers;

public:
    Board();
    ~Board();

    void loadBugsFromFile(const std::string& fileName);
    void displayBugs() ;
    void findBug(int id);
    void tapBoard();

    void displayLifeHistory();
    void displayLifeHistory() const;
    void writeLifeHistory() const;


    void runSimulation();
};

#endif //BOARD_H