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
        if (crawler->isAlive()) {
            crawler->move();
        }
    }
    map<pair<int, int>, vector<Crawler*>> cellMap;
    for (auto* crawler : crawlers) {
        if (crawler->isAlive()) {
            cellMap[{crawler->getPosition().x, crawler->getPosition().y}].push_back(crawler);
        }
    }
    for (auto& cell : cellMap) {
        if (cell.second.size() > 1) {
            vector<Crawler*> biggestBugs;
            int maxSize = 0;

            for (auto* bug : cell.second) {
                if (bug->getSize() > maxSize) {
                    maxSize = bug->getSize();
                    biggestBugs.clear();
                    biggestBugs.push_back(bug);
                } else if (bug->getSize() == maxSize) {
                    biggestBugs.push_back(bug);
                }
            }
            Crawler* winner;
            if (biggestBugs.size() > 1) {
                int randomIndex = rand() % biggestBugs.size();
                winner = biggestBugs[randomIndex];
            } else {
                winner = biggestBugs[0];
            }
            int totalSize = 0;
            for (auto* bug : cell.second) {
                if (bug != winner) {
                    totalSize += bug->getSize();
                    bug->setDead();
                    bug->setKillerId(winner->getId());
                    cout << "Bug " << bug->getId() << " was eaten by Bug " << winner->getId() << endl;
                }
            }
            if (totalSize > 0) {
                winner->setSize(winner->getSize() + totalSize);
                cout << "Bug " << winner->getId() << " grew to size " << winner->getSize() << endl;
            }
        }
    }
    int aliveCount = 0;
    Crawler* lastBug = nullptr;
    for (auto* crawler : crawlers) {
        if (crawler->isAlive()) {
            aliveCount++;
            lastBug = crawler;
        }
    }

    if (aliveCount == 1 && lastBug != nullptr) {
        cout << "Bug " << lastBug->getId() << " is the last bug standing!" << endl;
    }
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
    for (auto* crawler : crawlers) {
        if (crawler->isAlive()) {
            cellMap[{crawler->getPosition().x, crawler->getPosition().y}].push_back(crawler->getId());
        }
    }
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
