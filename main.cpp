#include <SFML/Graphics.hpp>

#include "boundary.h"
#include "ray.h"



int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");

    std::vector<Boundary> boundaries;
    int wall_count = 5;

    // create random boundaries
    for (int i = 0; i < wall_count; i++)
    {
        sf::Vector2f p1(rand() % 1000, rand() % 1000);
        sf::Vector2f p2(rand() % 1000, rand() % 1000);

        boundaries.push_back(Boundary(p1, p2));
    }

    std::vector<sf::Vector2f> cubePoints;
    cubePoints.push_back(sf::Vector2f(100, 100));
    cubePoints.push_back(sf::Vector2f(200, 100));
    cubePoints.push_back(sf::Vector2f(200, 200));
    cubePoints.push_back(sf::Vector2f(100, 200));

    boundaries.push_back(Boundary(cubePoints));
    
    Ray ray(sf::Vector2f(100, 450), sf::Vector2f(1, 0));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseMoved)
            {
                ray.intersection.hit = false;  
                ray.lookAt(event.mouseMove.x, event.mouseMove.y);  
            }
        }

        window.clear(sf::Color::Black);

        ray.castBoundary(boundaries);

        for (auto& boundary : boundaries){
            boundary.draw(window);
        }

        ray.draw(window);

        window.display();
    }

    return 0;
}