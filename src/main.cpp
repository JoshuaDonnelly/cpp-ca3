#include <iostream>
#include "../include/Crawler.h"
#include "../include/Board.h"
#include "../include/gui.h"

using namespace std;
int main() {
    Board board;


    int choice;
    int bugId;

    while (true) {
        cout << "\n===== Bug Game =====\n";
        cout << "1. Initialize Bug Board (load data from file) \n";
        cout << "2. Display all Bugs\n";
        cout << "3. Find a Bug (given an id)\n";
        cout << "4. Tap the Bug Board (cause all to move, then fight/eat)\n";
        cout << "5. Display life history of all bugs (path taken)\n";
        cout << "6. Display all cells listing their Bugs\n";
        cout << "7. Run Simulation (generates a tap every tenth of a second)\n";
        cout << "8. Load GUI\n";
        cout << "9. Exit (write life history of all Bugs to file)\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {

            case 1:
                board.loadBugsFromFile("crawler-bugs.txt");
                std::cout << "Bugs loaded successfully!\n";
                break;

            case 2:
                board.displayBugs();
                break;

            case 3:
                cout<<"Enter id to be found: ";
                cin >> bugId;
                board.findBug(bugId);
                break;
            case 4:
                board.tapBoard();
                break;
            case 5:
                board.displayLifeHistory();
                break;
            case 6 :
                board.displayCells();
                break;
            case 7: {
                int taps = 0;
                while (true) {
                    board.tapBoard();
                    taps++;
                    bool onlyOneLeft = true;
                    int aliveCount = 0;
                    for (int i = 0; i < 39; i++) {
                        board.tapBoard();
                        taps++;

                    }

                    cout << "Simulation complete after " << taps << " taps." << endl;
                    break;
                }
                break;
            }
            case 8:
                std::cout << "Launching GUI..." << std::endl;
                  gui( board);
                  break;
            case 9:
                board.writeLifeHistory();
                std::cout << "Life history written successfully!\n";
                std::cout << "Exiting...\n";
                return 0 ;
            default:
                cout << "Invalid Choice!\n";
        }
    }
}