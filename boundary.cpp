#include "boundary.h"
#include <cmath>

Boundary::Boundary(sf::Vector2f p1, sf::Vector2f p2)
{   
    Line line;

    line.p1 = p1;   
    line.p2 = p2;

    lines.push_back(line);
}

Boundary::Boundary(std::vector<sf::Vector2f> points){
    for (int i = 0; i < points.size() - 1; i++){
        Line line;

        line.p1 = points[i];
        line.p2 = points[i + 1];

        lines.push_back(line);
    }

    Line line;

    line.p1 = points[points.size() - 1];
    line.p2 = points[0];

    lines.push_back(line);
}

Boundary::Boundary(int segments, float radius, sf::Vector2f pos)
{
    float angle = 0;
    float angle_increment = 2 * M_PI / segments;

    for (int i = 0; i < segments; i++)
    {
        Line line;

        line.p1.x = pos.x + radius * cos(angle);
        line.p1.y = pos.y + radius * sin(angle);

        angle += angle_increment;

        line.p2.x = pos.x + radius * cos(angle);
        line.p2.y = pos.y + radius * sin(angle);

        lines.push_back(line);
    }
}

Boundary::Boundary(float sizeX, float sizeY, sf::Vector2f pos, float rotation){

    sf::Vector2f p1(-sizeX / 2, -sizeY / 2);
    sf::Vector2f p2(sizeX / 2, -sizeY / 2);
    sf::Vector2f p3(sizeX / 2, sizeY / 2);
    sf::Vector2f p4(-sizeX / 2, sizeY / 2);

    sf::Transform transform;
    transform.rotate(rotation);

    p1 = transform.transformPoint(p1);
    p2 = transform.transformPoint(p2);
    p3 = transform.transformPoint(p3);
    p4 = transform.transformPoint(p4);

    p1 += pos;
    p2 += pos;
    p3 += pos;
    p4 += pos;

    lines.push_back({p1, p2});
    lines.push_back({p2, p3});
    lines.push_back({p3, p4});
    lines.push_back({p4, p1});

}

void Boundary::draw(sf::RenderWindow& window) const
{
    for (auto& line : lines)
    {
        sf::Vertex line_vertices[] =
        {
            sf::Vertex(line.p1),
            sf::Vertex(line.p2)
        };

        window.draw(line_vertices, 2, sf::Lines);
    }
}
