#include "GameInstance.h"

GameInstance::GameInstance(uint width,uint height,int pov)
    :m_window(sf::VideoMode(width, height), "Use W,A,S,D for moving, wheel for chagne light range.", sf::Style::Close),
     m_start(width / 2, height / 2),
     m_player(m_start),
     m_engine(pov)
{
    m_hasDrawn = false;

    m_windowTexture.create(m_window.getSize().x, m_window.getSize().y);
    m_windowTexture.update(m_window);
    m_mask = m_windowTexture.copyToImage();

    m_wall.setFillColor(sf::Color::White);
    m_wall.setSize(sf::Vector2f(30,30));
}

void GameInstance::start()
{
    m_loop();
}

void GameInstance::m_loop()
{
    sf::Event event;

    while (m_window.isOpen()) {
        while (m_window.pollEvent(event)) {
            m_window.clear();

            // Processing key events
            m_events(event);

            // Getting positions
            const auto mousePosition = static_cast<sf::Vector2f>((sf::Mouse::getPosition()) - m_window.getPosition());
            const auto playerPosition = m_player.getPosition();

            // Calculate light mask
            const auto lightMask = m_engine.calculate(m_mask, playerPosition, mousePosition);

            // Drawing
            m_window.draw(lightMask);

            for (const auto & current : m_walls) {
                m_wall.setPosition(current.x, current.y);
                m_window.draw(m_wall);
            }

            // If added new wals, update scene mask
            if (m_hasDrawn) {
              m_windowTexture.update(m_window);
              m_mask = m_windowTexture.copyToImage();
              m_hasDrawn = false;
            }

            m_window.display();
        }
    }
}

void GameInstance::m_events(const sf::Event &event)
{
    switch (event.type) {
        case sf::Event::Closed:
            m_window.close();
        break;

        case sf::Event::MouseButtonReleased:
            m_walls.push_back(sf::Mouse::getPosition() - m_window.getPosition());
            m_hasDrawn = true;
        break;

        case sf::Event::KeyPressed:
            if(event.key.code == sf::Keyboard::W)
                m_player.top();
            else if(event.key.code == sf::Keyboard::S)
                m_player.bottom();
            else if(event.key.code == sf::Keyboard::A)
                m_player.left();
            else if(event.key.code == sf::Keyboard::D)
                m_player.right();
        break;

        case sf::Event::MouseWheelMoved:
            m_lightRange +=event.mouseWheel.delta;
            m_engine.setLightRange(m_lightRange * m_rangeWeight);
        break;

        default: break;
    }
}

