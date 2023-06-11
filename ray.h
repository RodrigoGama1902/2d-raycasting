#pragma once

#include <SFML/Graphics.hpp>

#include "boundary.h"

struct Intersection
{
    sf::Vector2f pt;
    bool hit;
};

class Ray
{
public:
    Ray(sf::Vector2f pos, sf::Vector2f direction);

    sf::Vector2f pos;
    sf::Vector2f direction;

    Intersection intersection;

    void draw(sf::RenderWindow& window) const;

    Intersection castLine(const Line& line);
    Intersection* closestIntersection(std::vector<Intersection>& intersections); 

    Intersection castBoundary(const Boundary& boundary);
    void castBoundary(const std::vector<Boundary>& boundaries);

    void lookAt(float x, float y);
};