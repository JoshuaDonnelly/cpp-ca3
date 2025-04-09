#include <SFML/Graphics.hpp>
#include "../include/Board.h"

int gui(Board& board)
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

    const int cellSize = 60;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        //display a 10x10 grid
        for (int x = 0; x < 10; x++) {
            for (int y = 0; y < 10; y++) {
                sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1));
                cell.setPosition(x * cellSize, y * cellSize);
                cell.setFillColor(sf::Color(50, 50, 50));
                window.draw(cell);
            }
        }
        //Drawing the bugs
        for (auto* bug: board.getCrawlers()) {
            if (bug->isAlive())
                continue;

            sf::CircleShape shape(20);
            shape.setFillColor(sf::Color::Green);

            Position pos = bug->getPosition();
            shape.setPosition(pos.x * cellSize + 10, pos.y * cellSize + 10);
            window.draw(shape);
        }
        window.display();
    }

    return 0;
}
