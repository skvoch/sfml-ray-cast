#ifndef UTILS_H
#define UTILS_H

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <math.h>

namespace Math {


    namespace Point {

        /// \brief Getting angle point on circle
        /// \param [in] angle
        /// \param [in] circle radis
        /// \param [in] circle center
        /// \return Point
        sf::Vector2f angle2Point(int angle,int radis,const sf::Vector2f& center)
        {
            sf::Vector2f reuslt;
            auto rad =  (angle *M_PI ) / 180;

            reuslt.x = static_cast<float>(radis * std::cos(rad)) + center.x;
            reuslt.y = static_cast<float>(radis * std::sin(rad)) + center.y;

            return reuslt;
        }

        /// \brief Getting point to angle on circle
        /// \param [in] point
        /// \param [in] circle center
        /// \return angle
        int pointToAngle(const sf::Vector2f& vec, const sf::Vector2f& center)
        {
            // may be auto
            int x = static_cast<int>(vec.x - center.x);
            int y = static_cast<int>(vec.y - center.y);
            if(x==0) return ( y > 0) ? 180 : 0;
            int a = static_cast<int>(std::atan(static_cast<double>(y) / static_cast<double>(x)) * 180 / M_PI);
            a = (x > 0) ? a + 90 : a + 270;
            return a;
        }
    }



    namespace Vector {

        /// \brief Getting vector lenght
        /// \param [in] const ref sf::VectorF
        /// \return Lenght
        float lenght(const sf::Vector2f &v) {
            return sqrt(v.x * v.x + v.y * v.y);
        }

        float pointsLenght(const sf::Vector2f &a,const sf::Vector2f b)
        {
            return std::sqrt((b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y));
        }
    }

    namespace Ray {

        /// \brief Cast the ray (use black-while mask)
        /// \param [in] const ref start point
        /// \param [in] const ref end point
        /// \param [in] const ref mask
        /// \return Point
        sf::Vector2f cast(sf::Vector2f start,const sf::Vector2f &end,const sf::Image &img, int lenght = 256) {
            // Grab the normalized vector
            sf::Vector2f u = end - start;
            u /= Math::Vector::lenght(u);

            sf::Rect<float> r(sf::Vector2f(0, 0), static_cast<sf::Vector2f>(img.getSize()));

            auto size = img.getSize();

            for(int i = 0; i<lenght;i++) {
                if (img.getPixel(std::min(static_cast<uint>(start.x),size.x), std::min(static_cast<uint>(start.y),size.y)) == sf::Color::White) {

                    return start;
                }

                start += u;
            }

            return start;
        }
    }
}
#endif // UTILS_H
