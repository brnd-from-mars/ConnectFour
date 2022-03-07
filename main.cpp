#include <iostream>
#include <SFML/graphics.hpp>


int main ()
{
    std::cout << "Hello, World!" << std::endl;

    sf::Window window(sf::VideoMode(800, 600), "Four Wins!");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
    }

    return 0;
}
