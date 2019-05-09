#include "RayEngine.h"
#include "Utils.h"
RayEngine::RayEngine(int pov)
    : m_pov(pov)
{

}

sf::VertexArray RayEngine::calculate(const sf::Image &mask,const sf::Vector2f &position,const sf::Vector2f &point)
{
    const auto step = m_pov / 2;
    const auto angle  = Math::Point::pointToAngle(point,position);

    std::vector<sf::Vector2f> points;
    points.reserve(static_cast<std::size_t>(m_pov));


    for(float i=-step; i < step; i+=1) {
        auto &from = position;
        auto to    = Math::Point::angle2Point(static_cast<int>(-90 + angle + i), 100, position);

        auto castedPoint = Math::Ray::cast(from , to, mask, m_lenghtRange);
        points.push_back(castedPoint);
    }

    sf::VertexArray result(sf::TriangleFan, points.size() + 1);
    result[0].position.x = position.x;
    result[0].position.y = position.y;
    result[0].color = m_color;

    auto colorStep = 255. / m_lenghtRange;

    for(std::size_t i =0;i<points.size();i++)
    {
        auto lenght = Math::Vector::pointsLenght(points[i],position);
        auto  color = static_cast<sf::Uint8>(static_cast<int>((m_lenghtRange - lenght)) * colorStep);


        result[i+1].position.x = points[i].x;
        result[i+1].position.y = points[i].y;
        result[i+1].color = sf::Color(color,color,0);
    }

    return result;
}

void RayEngine::setLightRange(int value)
{
    m_lenghtRange = value;
}
