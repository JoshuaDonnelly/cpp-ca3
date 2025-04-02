//
// Created by joshu on 01/04/2025.
//

#include "../include/Board.h"
#include "../include/Crawler.h"
#include "../include/Position.h"

#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>

Board::Board() {}

Board::~Board() {
    for (auto* crawler : crawlers) {
        delete crawler;
    }
    crawlers.clear();
}
void Board::loadBugsFromFile(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file) {
        std::cerr << "Error opening file " << fileName << std::endl;
        return;
    }

    char type;
    int id, x, y, dir, size;
    while (file >> type >> id >> x >> y >> dir >> size) {
        if (type == 'C') {
            Crawler* newBug = new Crawler(id, x, y, static_cast<Direction>(dir), size);
            crawlers.push_back(newBug);
            std::cout << "Loaded Bug: ID=" << id << " Position=(" << x << "," << y << ") Size=" << size << std::endl;
        } else {
            std::cerr << "Unrecognized bug type: " << type << std::endl;
        }
    }

    std::cout << "Total bugs loaded: " << crawlers.size() << std::endl;
}
void Board::displayBugs() {
    if (crawlers.empty()) {
        std::cout << "No bugs to display!" << std::endl;
    }
    else {
        for (auto* crawler : crawlers) {
            crawler->display();
        }
    }
}
void Board::findBug(int id) {
    for (auto* crawler : crawlers) {
        if (crawler->getId() == id) {
            crawler->display();
            return;
        }
    }
    std::cout << "Bug " << id << " not found." << std::endl;
}
void Board::tapBoard () {
    for (auto* crawler : crawlers) {
        crawler->move();
    }
    std::cout << "All bugs have moved." << std::endl;
}
