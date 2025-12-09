#include "pilka.h"

Pilka::Pilka(float x_in, float y_in, float vx_in, float vy_in, float r_in) {
    if (x_in <= 0) {
        x_in = 0;
    }
    if (x_in >= 640) {
        x_in = 100;
    }
    x = x_in;
    y = y_in;
    vx = vx_in;
    vy = vy_in;
    r = r_in;
    shape.setRadius(r);
    shape.setOrigin(r, r);
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color(244, 196, 48));
}

void Pilka::drukuj() {
    std::cout << " x=" << x
        << " y=" << y << " vx=" << vx << " vy=" << vy << "\n";
}

void Pilka::move() {
    x = x + vx;
    y = y + vy;
    shape.setPosition(x, y);
}

void Pilka::bounceX() {
    vx = -vx;
}

void Pilka::bounceY() {
    vy = -vy;
}

void Pilka::collideWalls(float width, float height) {
    
    if (x - r <= 0) {
        x = r;
        bounceX();
        std::cout << "HIT LEFT\n";
    }

    
    if (x + r >= width) {
        x = width - r;
        bounceX();
        std::cout << "HIT RIGHT\n";
    }

    
    if (y - r <= 0) {
        y = r;
        bounceY();
        std::cout << "HIT TOP\n";
    }

    
    if (y + r >= height) {
        std::cout << "HIT BOTTOM\n";
    }

    shape.setPosition(x, y);
}

bool Pilka::collidePaddle(const Paletka& p) {

    float palX = p.getX();
    float palY = p.getY();
    float palW = p.getSzerokosc();
    float palH = p.getWysokosc();

    
    bool nadpal = (x >= palX - palW / 2) && (x <= palX + palW / 2);
    bool gornapow = ((y + r) >= (palY - palH / 2)) && ((y - r) < (palY - palH / 2));

    if (nadpal && gornapow) {
        vy = -std::abs(vy);
        y = (palY - palH / 2) - r;
        shape.setPosition(x, y);
        return true;
    }
    return false;
}


void Pilka::reset(const sf::Vector2f& pozycja, const sf::Vector2f& predkosc)
{
    x = pozycja.x;
    y = pozycja.y;
    vx = predkosc.x;
    vy = predkosc.y;
    shape.setPosition(x, y);
}
