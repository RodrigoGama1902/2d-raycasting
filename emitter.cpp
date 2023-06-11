#include "emitter.h"

Emitter::Emitter(int rays, sf::Vector2f pos){

    ray_count = rays;
    createEmitter(pos);
}

void Emitter::createEmitter(sf::Vector2f pos){
        
    float angle_increment = 2 * M_PI / ray_count;

    for (int i = 0; i < ray_count; i++)
    {
        Ray ray(pos, sf::Vector2f(cos(angle), sin(angle)));
        rays.push_back(ray);

        angle += angle_increment;
    }
}

void Emitter::draw(sf::RenderWindow& window) const
{
    for (auto& ray : rays)
    {
        ray.draw(window);
    }
}

void Emitter::castBoundary(const std::vector<Boundary>& boundaries)
{
    for (auto& ray : rays)
    {
        ray.castBoundary(boundaries);
    }
}

void Emitter::setPos(sf::Vector2f pos)
{
    for (auto& ray : rays)
    {
        ray.pos = pos;
    }
    }