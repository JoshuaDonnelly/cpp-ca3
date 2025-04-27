#include "../include/Board.h"
#include "../include/Crawler.h"
#include "../include/Hopper.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <ctime>
#include <map>
using namespace std;
Board::Board() {}

Board::~Board() {
    for (auto* bug : bugs) {
        delete bug;
    }
    bugs.clear();
}

void Board::loadBugsFromFile(const string& fileName) {
    ifstream file(fileName);
    if (!file) {
        cerr << "Error opening file " << fileName << endl;
        return;
    }

    char type;
    int id, x, y, dir, size, hopLength;
    while (file >> type >> id >> x >> y >> dir >> size) {
        if (type == 'H') {
            file >> hopLength;
            bugs.push_back(new Hopper(id, x, y, static_cast<Direction>(dir), size, hopLength));
            cout << "Loaded Hopper: ID=" << id << " HopLength=" << hopLength << endl;
        }
        else if (type == 'C') {
            bugs.push_back(new Crawler(id, x, y, static_cast<Direction>(dir), size));
            cout << "Loaded Crawler: ID=" << id << endl;
        }
        else {
            cerr << "Unrecognized bug type: " << type << endl;
        }
    }
}

void Board::displayBugs() const {
    if (bugs.empty()) {
        cout << "No bugs to display!" << endl;
    } else {
        for (const auto* bug : bugs) {
            bug->display();
        }
    }
}

Bug* Board::findBug(int id) {
    for (auto* bug : bugs) {
        if (bug->getId() == id) {
            bug->display();
            return bug;
        }
    }
    cout << "Bug " << id << " not found." << endl;
    return nullptr;
}

void Board::tapBoard() {
    // Move all bugs
    for (auto* bug : bugs) {
        if (bug->isAlive()) {
            bug->move();
        }
    }

    // Check for fights
    map<pair<int, int>, vector<Bug*>> cellMap;
    for (auto* bug : bugs) {
        if (bug->isAlive()) {
            cellMap[{bug->getPosition().x, bug->getPosition().y}].push_back(bug);
        }
    }

    for (auto& cell : cellMap) {
        if (cell.second.size() > 1) {
            vector<Bug*> biggestBugs;
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

            Bug* winner;
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
                    cout << bug->getType() << " " << bug->getId()
                              << " was eaten by " << winner->getType()
                              << " " << winner->getId() << endl;
                }
            }

            if (totalSize > 0) {
                winner->setSize(winner->getSize() + totalSize);
                cout << winner->getType() << " " << winner->getId()
                          << " grew to size " << winner->getSize() << endl;
            }
        }
    }

    // Check for game over
    int aliveCount = 0;
    Bug* lastBug = nullptr;
    for (auto* bug : bugs) {
        if (bug->isAlive()) {
            aliveCount++;
            lastBug = bug;
        }
    }

    if (aliveCount == 1 && lastBug != nullptr) {
        cout << lastBug->getType() << " " << lastBug->getId()
                  << " is the last bug standing!" << endl;
    }
}

void Board::displayCells() const {
    map<pair<int, int>, vector<string>> cellMap;
    for (const auto* bug : bugs) {
        if (bug->isAlive()) {
            cellMap[{bug->getPosition().x, bug->getPosition().y}]
                .push_back(bug->getType() + " " + to_string(bug->getId()));
        }
    }

    for (int y = 0; y < 10; ++y) {
        for (int x = 0; x < 10; ++x) {
            cout << "(" << x << "," << y << "): ";
            auto it = cellMap.find({x, y});
            if (it != cellMap.end() && !it->second.empty()) {
                for (size_t i = 0; i < it->second.size(); ++i) {
                    cout << it->second[i];
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

void Board::displayLifeHistory() const {
    cout << "Bug Life History:\n";
    for (const auto* bug : bugs) {
        bug->displayLifeHistory();
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

    for (const auto* bug : bugs) {
        bug->writeLifeHistory(outFile);
    }

    outFile.close();
    cout << "Life history saved to " << filename << endl;
}

void Board::runSimulation() {
    ofstream outFile("simulation_results.txt");
    int iterations = 0;

    while (iterations < 100) {
        tapBoard();
        displayBugs();

        outFile << "Iteration " << iterations << ":\n";
        for (const auto* bug : bugs) {
            outFile << bug->getType() << " " << bug->getId()
                    << " at (" << bug->getPosition().x << ", "
                    << bug->getPosition().y << ")\n";
        }
        outFile << "\n";

        iterations++;
    }

    outFile.close();
    cout << "Simulation completed after " << iterations << " iterations.\n";
}