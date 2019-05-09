#ifndef GAMEINSTANCE_H
#define GAMEINSTANCE_H

#include <SFML/Graphics.hpp>

#include "RayEngine.h"
#include "Player.h"



class GameInstance
{
public:
    /// \param [in] wWindow width
    /// \param [in] Window height
    /// \param [in] Player pov
    GameInstance(uint width, uint height, int pov);

    /// \brief Start game loop
    void start();
private:
    void m_loop();

    void m_events(const sf::Event &event);

    bool m_hasDrawn;
    int  m_lightRange = 10;
    int  m_rangeWeight = 25;


    sf::RenderWindow m_window;
    sf::Image m_mask;
    sf::Texture m_windowTexture;
    sf::RectangleShape m_wall;
    sf::Vector2f m_start;

    std::vector<sf::Vector2i> m_walls;

    Player m_player;
    RayEngine m_engine;
};

#endif // GAMEINSTANCE_H
