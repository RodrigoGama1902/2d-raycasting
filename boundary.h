#pragma once

#include <SFML/Graphics.hpp>

struct Line
{
    sf::Vector2f p1;
    sf::Vector2f p2;
};

class Boundary
{
public:
    Boundary(sf::Vector2f p1, sf::Vector2f p2); // Creates a line
    Boundary(std::vector<sf::Vector2f> points); // Creates a polygon

    std::vector<Line> lines;

    void draw(sf::RenderWindow& window) const; 
    
};