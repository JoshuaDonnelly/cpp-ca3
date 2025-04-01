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
};



#endif //BOARD_H
