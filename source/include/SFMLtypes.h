#ifndef SFMLTYPES_H
#define SFMLTYPES_H

#include "SFML/Graphics.hpp"
#include "SFML/System/Vector2.hpp"



typedef sf::Vector2i iVector2;

typedef sf::Vector2f fVector2;

typedef sf::RectangleShape RectangleShape;

typedef sf::CircleShape CircleShape;

typedef sf::Color Color;

namespace GameColor {
    inline const auto White  = Color::White;
    inline const auto Black  = Color::Black;
    inline const auto Red    = Color(217, 69, 69);
    inline const auto Blue   = Color(69, 116, 217);
    inline const auto Yellow = Color(217, 190, 69);
    inline const auto Magenta= Color(217, 69, 141);
    inline const auto Green  = Color(121, 217, 69);
    inline const auto Cyan   = Color(69, 217, 153);
    inline const auto Gray   = Color(150,150,180);
    inline const auto Orange = Color(217, 121, 69);
    inline const auto Purple = Color(131, 69, 217);
    inline const auto Darkgreen = Color(6, 78, 64);
}



/*
namespace Color {
    inline const auto White  = sf::Color::White;
    inline const auto Black  = sf::Color::Black;
    inline const auto Red    = sf::Color::Red;
    inline const auto Blue   = sf::Color::Blue;
    inline const auto Yellow = sf::Color::Yellow;
    inline const auto Magenta= sf::Color::Magenta;
    inline const auto Green  = sf::Color::Green;
    inline const auto Cyan   = sf::Color::Cyan;
    inline const auto Gray   = sf::Color(150,150,150);
}*/

#endif