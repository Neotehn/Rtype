#include <iostream>
#include "SFML/Graphics.hpp"

int main() {
    std::cout << "Hello, World Client!" << std::endl;
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.display();
    }
    return 0;
}
