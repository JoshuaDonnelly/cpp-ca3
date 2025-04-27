#include <SFML/Graphics.hpp>
#include "../include/Board.h"

int gui(Board& board) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Bug's Life Simulation");
    const int cellSize = 60;
    sf::Clock clock;
    bool gameRunning = true;

    while (window.isOpen() && gameRunning) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Tap board and check game state every 0.1 seconds
        if (clock.getElapsedTime().asSeconds() > 0.1f) {
            board.tapBoard();
            clock.restart();

            // Count alive bugs after each tap
            int aliveCount = 0;
            for (auto* bug : board.getBugs()) {
                if (bug->isAlive()) aliveCount++;
            }

            // End game if only one bug left
            if (aliveCount <= 1) {
                gameRunning = false;
                window.close();
            }
        }

        // Draw everything
        window.clear(sf::Color::Black);

        // Draw grid
        for (int x = 0; x < 10; x++) {
            for (int y = 0; y < 10; y++) {
                sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1));
                cell.setPosition(x * cellSize, y * cellSize);
                cell.setFillColor(sf::Color(50, 50, 50));
                window.draw(cell);
            }
        }

        // Draw bugs
        for (auto* bug : board.getBugs()) {
            // In the bug drawing section:
            for (auto* bug : board.getBugs()) {
                if (!bug->isAlive()) continue;

                sf::CircleShape shape(20);
                if (bug->getType() == "Crawler") {
                    shape.setFillColor(sf::Color::Green);
                }
                else if (bug->getType() == "Hopper") {
                    shape.setFillColor(sf::Color::Blue);
                }
                else if (bug->getType() == "Spider") {
                    shape.setFillColor(sf::Color::Red);
                }

                Position pos = bug->getPosition();
                shape.setPosition(pos.x * cellSize + 10, pos.y * cellSize + 10);
                window.draw(shape);
            }
        }

        window.display();
    }
    return 0;
}