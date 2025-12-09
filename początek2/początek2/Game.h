#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <string>

#include "pilka.h"
#include "paletka.h"
#include "Stonge.h"
#include "GameState.h"

class Game
{
public:
    Game();

    void zresetujGre();

    
    void update(sf::Time dt);

    
    void render(sf::RenderTarget& target);

    
    bool zapiszGre(const std::string& nazwaPliku);
    bool wczytajGre(const std::string& nazwaPliku);

    
    int pobierzPunkty() const { return punktyGracza; }

private:
    Paletka m_paletka;
    Pilka m_pilka;
    std::vector<Stone> m_bloki;

    GameState m_snapshot;  

    int punktyGracza;    

    const float WIDTH = 800.f;
    const float HEIGHT = 600.f;
};
