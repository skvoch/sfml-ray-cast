#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player
{
public:
    Player(const sf::Vector2f &m_position);

    /// \brief Move to left
    void left();

    /// \brief Move to right
    void right();

    /// \brief Move to top
    void top();

    /// \brief Move to bottom
    void bottom();

    /// \brief Getting player position
    sf::Vector2f getPosition();
private:
    float m_speed = 5;
    sf::Vector2f m_position;
};



#endif // PLAYER_H
