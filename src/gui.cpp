#include <SFML/Graphics.hpp>
#include "../include/Board.h"

int gui(Board& board) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Bug's Life Simulation");
    const int cellSize = 60;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

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
            if (!bug->isAlive()) continue;

            sf::CircleShape shape(20);
            if (bug->getType() == "Crawler") {
                shape.setFillColor(sf::Color::Green);
            } else if (bug->getType() == "Hopper") {
                shape.setFillColor(sf::Color::Blue);
            }

            Position pos = bug->getPosition();
            shape.setPosition(pos.x * cellSize + 10, pos.y * cellSize + 10);
            window.draw(shape);
        }

        window.display();
    }

    return 0;
}