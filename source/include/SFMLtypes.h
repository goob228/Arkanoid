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
    inline const auto Red    = Color::Red;
    inline const auto Blue   = Color::Blue;
    inline const auto Yellow = Color::Yellow;
    inline const auto Magenta= Color::Magenta;
    inline const auto Green  = Color::Green;
    inline const auto Cyan   = Color::Cyan;
    inline const auto Gray   = Color(150,150,180);
    inline const auto Orange = Color(255,120,1);
    inline const auto Hazel  = Color(142,118,24);
    inline const auto Purple = Color(120, 60, 159);
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