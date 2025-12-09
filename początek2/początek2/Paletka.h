#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Paletka
{
public:
    Paletka(float x_in, float y_in, float szerokosc_in, float wysokosc_in, float predkosc_in);

    
    void moveLeft() { x = x - predkosc; shape.setPosition(x, y); }
    void moveRight() { x = x + predkosc; shape.setPosition(x, y); }

    void clampToBounds(float width) {
        
        if (x - szerokosc / 2 < 0) {
            x = szerokosc / 2;
        }
        if (x + szerokosc / 2 > width) {
            x = width - szerokosc / 2;
        }
        shape.setPosition(x, y);
    }

    void draw(sf::RenderTarget& target) const {
        target.draw(shape);
    }

    float getX() const { return x; }
    float getY() const { return y; }
    float getSzerokosc() const { return szerokosc; }
    float getWysokosc() const { return wysokosc; }

    
    void setPosition(const sf::Vector2f& nowaPozycja) {
        x = nowaPozycja.x;
        y = nowaPozycja.y;
        shape.setPosition(x, y);
    }

private:
    float x, y;
    float szerokosc;
    float wysokosc;
    float predkosc;
    sf::RectangleShape shape;
};
