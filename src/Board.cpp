//
// Created by joshu on 01/04/2025.
//

#include "../include/Board.h"
#include "../include/Crawler.h"
#include "../include/Position.h"


#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>
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
void Board::displayLifeHistory() {
    std::cout << "Bug Life History:\n";

    for (auto* crawler : crawlers) {
        std::cout << "Bug ID: " << crawler->getId() << " Path: ";

        // Print each position in the bug's path
        for (const Position& pos : crawler->getPath()) {
            std::cout << "(" << pos.x << "," << pos.y << ") ";
        }

        // Check if the bug was eaten
        if (!crawler->isAlive()) {
            std::cout << " Eaten by Bug " << crawler->getKillerId();
        }

        std::cout << std::endl;
    }
}


void Board::writeLifeHistory() const {
    std::time_t now = std::time(nullptr);
    char filename[100];
    std::strftime(filename, sizeof(filename), "bugs_life_history_%Y-%m-%d_%H-%M-%S.out", std::localtime(&now));

    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Error: Unable to create life history file.\n";
        return;
    }
    for (const auto* crawler : crawlers) {
        crawler->writeLifeHistory(outFile);
    }

    outFile.close();
    std::cout << "Life history saved to " << filename << std::endl;
}
void Board::runSimulation() {
    using namespace std::chrono_literals;
    std::ofstream outFile("simulation_results.txt");

    int iterations = 0;
    while (true) {
        tapBoard();
        displayBugs();  // Assuming this displays progress

        // Write progress to file
        outFile << "Iteration " << iterations << ":\n";
        for (const auto& crawler : crawlers) {
            outFile << "Bug " << crawler->getId() << " is at position ("
                    << crawler->getPosition().x << ", "
                    << crawler->getPosition().y << ")\n";
        }
        outFile << "\n";

        // Check game-over condition (example: after 100 iterations)
        if (++iterations >= 100) {
            break;
        }

        std::this_thread::sleep_for(0.1s);
    }

    outFile.close();
    std::cout << "Simulation completed and results written to file.\n";
}