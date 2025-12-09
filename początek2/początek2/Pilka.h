#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "paletka.h"

class Pilka {
public:
    Pilka(float x_in, float y_in, float vx_in, float vy_in, float r_in);

    void move();
    void bounceX();
    void bounceY();
    void collideWalls(float width, float height);
    void drukuj();

    
    float getX() const { return x; }
    float getY() const { return y; }
    float getVX() const { return vx; }
    float getVY() const { return vy; }
    float getRadius() const { return r; }

    void draw(sf::RenderTarget& target) const { target.draw(shape); }
    bool collidePaddle(const Paletka& p);

    
    void reset(const sf::Vector2f& pozycja, const sf::Vector2f& predkosc);

private:
    float x;
    float y;
    float vx;
    float vy;
    float r;
    sf::CircleShape shape;
};
