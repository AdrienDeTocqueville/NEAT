#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Pool.h"
#include "Network.h"

int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(512, 512), "N.E.A.T.");
    window.setFramerateLimit(30);

    Pool pool(300, 3, 1);
//    for (Species& s: pool.species)
//    {
//        for (Genome& genome: s.genomes)
//        {
//            genome.computeFitness();
//        }
//    }
//
//    pool.buildNewGeneration();


    sf::Event event;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        window.display();
    }

    return 0;
}
