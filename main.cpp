#include <SFML/Graphics.hpp>

#include "boundary.h"
#include "ray.h"



int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");

    std::vector<Boundary> boundaries;
    
    // Create random line boundaries

    int line_count = 3;
    for (int i = 0; i < line_count; i++)
    {
        sf::Vector2f p1(rand() % 1000, rand() % 1000);
        sf::Vector2f p2(rand() % 1000, rand() % 1000);

        boundaries.push_back(Boundary(p1, p2));
    }

    // Create a polygon boundary
    std::vector<sf::Vector2f> polygonPoints;
    polygonPoints.push_back(sf::Vector2f(100, 100));
    polygonPoints.push_back(sf::Vector2f(200, 100));
    polygonPoints.push_back(sf::Vector2f(200, 200));
    polygonPoints.push_back(sf::Vector2f(100, 200));
    boundaries.push_back(Boundary(polygonPoints));

    // Create a circle
    boundaries.push_back(Boundary(100, 100, sf::Vector2f(500, 500)));
    
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