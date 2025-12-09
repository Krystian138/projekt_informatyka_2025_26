#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "paletka.h"
#include "pilka.h"
#include "Stonge.h"

// 1. Struktura pomocnicza
struct BlockData
{
    float x;
    float y;
    int hp;
};

// 2. Klasa GameState przechowuj¹ca stan gry (snapshot)
class GameState
{
public:
    GameState() = default;

    GameState(const Paletka& paddle,
        const Pilka& ball,
        const std::vector<Stone>& blocks)
    {
        capture(paddle, ball, blocks);
    }

    // zapisanie aktualnego stanu obiektów do pól klasy
    void capture(const Paletka& paddle,
        const Pilka& ball,
        const std::vector<Stone>& blocks);

    // Zapis stanu do pliku tekstowego
    bool saveToFile(const std::string& nazwaPliku) const;

    // Odczyt stanu z pliku tekstowego
    bool loadFromFile(const std::string& nazwaPliku);

    // Zastosowanie wczytanego stanu do obiektów gry
    void apply(Paletka& paletka,
        Pilka& pilka,
        std::vector<Stone>& bloki) const;

    // ewentualne gettery
    const sf::Vector2f& getPaddlePosition() const { return paddlePosition; }
    const sf::Vector2f& getBallPosition()   const { return ballPosition; }
    const sf::Vector2f& getBallVelocity()   const { return ballVelocity; }
    const std::vector<BlockData>& getBlocks() const { return this->blocks; }

private:
    sf::Vector2f paddlePosition;       // pozycja paletki
    sf::Vector2f ballPosition;         // pozycja pi³ki
    sf::Vector2f ballVelocity;         // prêdkoœæ pi³ki
    std::vector<BlockData> blocks;     // stany wszystkich klocków
};
