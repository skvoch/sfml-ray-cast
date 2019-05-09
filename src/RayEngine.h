#ifndef RAYENGINE_H
#define RAYENGINE_H

#include <SFML/Graphics.hpp>
#include <iostream>

class RayEngine
{
public:
    RayEngine(int pov);

    /// \brief Calculate rays vertex by mask
    /// \param [in] mask
    /// \return
    sf::VertexArray calculate(const sf::Image &mask, const sf::Vector2f &position, const sf::Vector2f &point);


    /// \brief Setting light range
    /// \param [in] value
    void setLightRange(int value);
private:
    int m_pov = 90;
    int m_angle;
    int m_lenghtRange = 256;

    sf::Color m_color = sf::Color::Yellow;
};

#endif // RAYENGINE_H
