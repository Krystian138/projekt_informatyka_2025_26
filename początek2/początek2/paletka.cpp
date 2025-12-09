#include "paletka.h"

Paletka::Paletka(float x_in, float y_in, float szerokosc_in, float wysokosc_in, float predkosc_in) {
    x = x_in;
    y = y_in;
    szerokosc = szerokosc_in;
    wysokosc = wysokosc_in;
    predkosc = predkosc_in;
    shape.setSize({ szerokosc, wysokosc });
    shape.setOrigin(szerokosc / 2, wysokosc / 2);
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color(255, 0, 255));
}
