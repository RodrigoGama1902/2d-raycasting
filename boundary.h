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
    Boundary(int segments, float radius, sf::Vector2f pos); // Creates a circle
    Boundary(float sizeX, float sizeY, sf::Vector2f pos, float rotation); // Creates a rectangle

    std::vector<Line> lines;

    void draw(sf::RenderWindow& window) const; 
    
};