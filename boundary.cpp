#include "boundary.h"

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
