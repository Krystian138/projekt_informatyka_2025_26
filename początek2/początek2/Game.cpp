#include "Game.h"
#include <fstream>
#include <cstdlib> 

namespace
{
    
    bool kolizjaKoloProstokat(float cx, float cy, float r, const sf::FloatRect& rect)
    {
        float najblizszyX = std::max(rect.left, std::min(cx, rect.left + rect.width));
        float najblizszyY = std::max(rect.top, std::min(cy, rect.top + rect.height));
        float dx = cx - najblizszyX;
        float dy = cy - najblizszyY;
        return (dx * dx + dy * dy) <= (r * r);
    }
}

Game::Game()
    : m_paletka(400.f, 540.f, 100.f, 20.f, 8.f),   
    m_pilka(400.f, 300.f, 4.f, 3.f, 8.f),        
    punktyGracza(0)
{
    const int ILOSC_KOLUMN = 6;
    const int ILOSC_WIERSZY = 7;
    const float ROZMIAR_BLOKU_Y = 25.f;
    const float ROZMIAR_BLOKU_X = (WIDTH - (ILOSC_KOLUMN - 1) * 2.f) / ILOSC_KOLUMN;

    m_bloki.clear();
    m_bloki.reserve(ILOSC_KOLUMN * ILOSC_WIERSZY);

    for (int y = 0; y < ILOSC_WIERSZY; ++y)
    {
        for (int x = 0; x < ILOSC_KOLUMN; ++x)
        {
            float posX = x * (ROZMIAR_BLOKU_X + 2.f);
            float posY = 50.f + y * (ROZMIAR_BLOKU_Y + 2.f);

            
            int zycia = (y < 1) ? 3 :
                (y < 3) ? 2 :
                1;

            m_bloki.emplace_back(
                sf::Vector2f(posX, posY),
                sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y),
                zycia
            );
        }
    }
}

void Game::zresetujGre()
{
    
    m_paletka = Paletka(400.f, 540.f, 100.f, 20.f, 8.f);
    m_pilka = Pilka(400.f, 300.f, 4.f, 3.f, 8.f);

    
    punktyGracza = 0;

    
    m_bloki.clear();

    const int ILOSC_KOLUMN = 6;
    const int ILOSC_WIERSZY = 7;
    const float ROZMIAR_BLOKU_Y = 25.f;
    const float ROZMIAR_BLOKU_X =
        (WIDTH - (ILOSC_KOLUMN - 1) * 2.f) / ILOSC_KOLUMN;

    for (int y = 0; y < ILOSC_WIERSZY; ++y)
    {
        for (int x = 0; x < ILOSC_KOLUMN; ++x)
        {
            float posX = x * (ROZMIAR_BLOKU_X + 2.f);
            float posY = 50.f + y * (ROZMIAR_BLOKU_Y + 2.f);

            int zycia = (y < 1) ? 3 :
                (y < 3) ? 2 :
                1;

            m_bloki.emplace_back(
                sf::Vector2f(posX, posY),
                sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y),
                zycia
            );
        }
    }
}


void Game::update(sf::Time )
{
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_paletka.moveLeft();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_paletka.moveRight();
    }
    m_paletka.clampToBounds(WIDTH);

    
    m_pilka.move();
    m_pilka.collideWalls(WIDTH, HEIGHT);

    
    m_pilka.collidePaddle(m_paletka);

    
    float bx = m_pilka.getX();
    float by = m_pilka.getY();
    float br = 8.f; 

    for (auto& blok : m_bloki)
    {
        if (blok.isDestroyed())
            continue;

        sf::FloatRect prostokat = blok.getGlobalBounds();

        if (kolizjaKoloProstokat(bx, by, br, prostokat))
        {
            
            m_pilka.bounceY();

            int zyciaPrzed = blok.getHP();
            blok.trafienie();
            int zyciaPo = blok.getHP();

            if (zyciaPo < zyciaPrzed)
            {
                
                punktyGracza += 10;

                
                if (zyciaPo <= 0)
                {
                    punktyGracza += 40;
                }
            }

            
            break;
        }
    }

    
    if (m_pilka.getY() - br > HEIGHT)
    {
        std::cout << "MISS! KONIEC GRY\n";

        
        std::ofstream plikWyniki("wyniki.txt", std::ios::app);
        if (plikWyniki.is_open())
        {
            plikWyniki << punktyGracza << "\n";
        }

        
        std::exit(0);
    }

    
}

void Game::render(sf::RenderTarget& target)
{
    
    m_paletka.draw(target);
    m_pilka.draw(target);

    for (const auto& blok : m_bloki)
    {
        if (!blok.isDestroyed())
        {
            blok.draw(target);
        }
    }
}


bool Game::zapiszGre(const std::string& nazwaPliku)
{
    m_snapshot.capture(m_paletka, m_pilka, m_bloki);
    bool sukces = m_snapshot.saveToFile(nazwaPliku);
    return sukces;
}


bool Game::wczytajGre(const std::string& nazwaPliku)
{
    GameState stan;
    if (!stan.loadFromFile(nazwaPliku))
        return false;

    stan.apply(m_paletka, m_pilka, m_bloki);
    m_snapshot = stan; 
    return true;
}
