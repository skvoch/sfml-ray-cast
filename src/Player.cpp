#include "Player.h"

Player::Player(const sf::Vector2f &position)
    : m_position(position)
{

}

void Player::left()
{
   m_position.x -=m_speed;
}

void Player::right()
{
    m_position.x +=m_speed;
}

void Player::top()
{
    m_position.y-=m_speed;
}

void Player::bottom()
{
    m_position.y +=m_speed;
}

sf::Vector2f Player::getPosition()
{
    return m_position;
}
