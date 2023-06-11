#include "ray.h"
#include "boundary.h"

#include <cmath>

Ray::Ray(sf::Vector2f pos, sf::Vector2f direction)
{
    this->pos = pos;
    this->direction = direction;
    intersection = { {0,0}, false };
}

void Ray::draw(sf::RenderWindow& window) const
{
    sf::Vertex line[] =
    {
        sf::Vertex(pos),
        sf::Vertex(pos + direction)
    };

    window.draw(line, 2, sf::Lines);

    if (intersection.hit == true)
    {
        sf::CircleShape circle(5);
        circle.setOrigin(5, 5);
        circle.setPosition(intersection.pt);
        circle.setFillColor(sf::Color::Red);

        window.draw(circle);
    }
}

Intersection Ray::castBoundary(const Boundary& boundary)
{   

    std::vector<Intersection> intersections;

    for (auto& line : boundary.lines){

        float x1 = line.p1.x;
        float y1 = line.p1.y;
        float x2 = line.p2.x;
        float y2 = line.p2.y;

        float x3 = pos.x;
        float y3 = pos.y;
        float x4 = pos.x + direction.x;
        float y4 = pos.y + direction.y;

        float den = (x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4);

        if (den == 0)
            return { {0,0}, false };

        float t = ((x1 - x3)*(y3 - y4) - (y1 - y3)*(x3 - x4)) / den;
        float u = -((x1 - x2)*(y1 - y3) - (y1 - y2)*(x1 - x3)) / den;

        if (t > 0 && t < 1 && u > 0)
        {   
            sf::Vector2f pt;
            pt.x = x1 + t * (x2 - x1);
            pt.y = y1 + t * (y2 - y1);

            intersections.push_back({ pt, true });
        }
    }

    Intersection* closest = nullptr;
    
    for (auto& intersection : intersections)
    {
        if (!intersection.hit){
            continue;
        }

        if (closest == nullptr)
        {
            closest = &intersection;
            continue;
        }

        float d1 = sqrt(pow(pos.x - intersection.pt.x, 2) + pow(pos.y - intersection.pt.y, 2));
        float d2 = sqrt(pow(pos.x - closest->pt.x, 2) + pow(pos.y - closest->pt.y, 2));

        if (d1 < d2)
            closest = &intersection;
    }

    if (closest != nullptr){
        return *closest;
    }

    return { {0,0}, false };
}

void Ray::castBoundary(const std::vector<Boundary>& boundaries)
{   
    std::vector<Intersection> intersections;

    for (auto& boundary : boundaries)
        intersections.push_back(castBoundary(boundary));

    Intersection* closest = nullptr;
    
    for (auto& intersection : intersections)
    {
        if (!intersection.hit){
            continue;
        }

        if (closest == nullptr)
        {
            closest = &intersection;
            continue;
        }

        float d1 = sqrt(pow(pos.x - intersection.pt.x, 2) + pow(pos.y - intersection.pt.y, 2));
        float d2 = sqrt(pow(pos.x - closest->pt.x, 2) + pow(pos.y - closest->pt.y, 2));

        if (d1 < d2)
            closest = &intersection;
    }

    if (closest != nullptr){
        this->intersection = *closest;
        return;
    }

    this->intersection = { {0,0}, false };
    return;
}


void Ray::lookAt(float x, float y)
{
    direction.x = x - pos.x;
    direction.y = y - pos.y;
}