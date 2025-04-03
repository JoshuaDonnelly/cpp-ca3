/*
 * Board.cpp
 * Created by joshu on 01/04/2025.
 */

#include "../include/Board.h"
#include "../include/Crawler.h"
#include "../include/Position.h"

#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <ctime>
#include <map>
#include <vector>

using namespace std;

Board::Board() {}

Board::~Board() {
    for (auto* crawler : crawlers) {
        delete crawler;
    }
    crawlers.clear();
}

void Board::loadBugsFromFile(const string& fileName) {
    ifstream file(fileName);
    if (!file) {
        cerr << "Error opening file " << fileName << endl;
        return;
    }

    char type;
    int id, x, y, dir, size;
    while (file >> type >> id >> x >> y >> dir >> size) {
        if (type == 'C') {
            Crawler* newBug = new Crawler(id, x, y, static_cast<Direction>(dir), size);
            crawlers.push_back(newBug);
            cout << "Loaded Bug: ID=" << id << " Position=(" << x << "," << y << ") Size=" << size << endl;
        } else {
            cerr << "Unrecognized bug type: " << type << endl;
        }
    }

    cout << "Total bugs loaded: " << crawlers.size() << endl;
}

void Board::displayBugs() {
    if (crawlers.empty()) {
        cout << "No bugs to display!" << endl;
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
    cout << "Bug " << id << " not found." << endl;
}

void Board::tapBoard() {
    for (auto* crawler : crawlers) {
        crawler->move();
    }
    cout << "All bugs have moved." << endl;
}

void Board::displayLifeHistory() {
    cout << "Bug Life History:\n";

    for (auto* crawler : crawlers) {
        cout << "Bug ID: " << crawler->getId() << " Path: ";

        for (const Position& pos : crawler->getPath()) {
            cout << "(" << pos.x << "," << pos.y << ") ";
        }

        if (!crawler->isAlive()) {
            cout << " Eaten by Bug " << crawler->getKillerId();
        }

        cout << endl;
    }
}

void Board::writeLifeHistory() const {
    time_t now = time(nullptr);
    char filename[100];
    strftime(filename, sizeof(filename), "bugs_life_history_%Y-%m-%d_%H-%M-%S.out", localtime(&now));

    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error: Unable to create life history file.\n";
        return;
    }
    for (const auto* crawler : crawlers) {
        crawler->writeLifeHistory(outFile);
    }

    outFile.close();
    cout << "Life history saved to " << filename << endl;
}

void Board::displayCells() {
    map<pair<int, int>, vector<int>> cellMap;

    // Populate the map with crawler positions
    for (auto* crawler : crawlers) {
        if (crawler->isAlive()) {  // Only show alive bugs
            cellMap[{crawler->getPosition().x, crawler->getPosition().y}].push_back(crawler->getId());
        }
    }

    // Display the grid (10x10 grid to match movement logic)
    for (int y = 0; y < 10; ++y) {
        for (int x = 0; x < 10; ++x) {
            cout << "(" << x << "," << y << "): ";
            auto it = cellMap.find({x, y});
            if (it != cellMap.end() && !it->second.empty()) {
                for (size_t i = 0; i < it->second.size(); ++i) {
                    cout << "Crawler " << it->second[i];
                    if (i != it->second.size() - 1) {
                        cout << ", ";
                    }
                }
            } else {
                cout << "empty";
            }
            cout << endl;
        }
    }
}
