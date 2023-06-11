#pragma once

#include <SFML/Graphics.hpp>

#include "boundary.h"
#include "ray.h"

#include <cmath>

class Emitter
{   
public:

    int ray_count;
    float angle;

    std::vector<Ray> rays;

    Emitter(int rays, sf::Vector2f pos);
    
    void createEmitter(sf::Vector2f pos);
    void draw(sf::RenderWindow& window) const;
    void castBoundary(const std::vector<Boundary>& boundaries);
    void setPos(sf::Vector2f pos);
};