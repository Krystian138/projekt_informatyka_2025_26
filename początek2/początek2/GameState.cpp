#include "GameState.h"
#include <fstream>

void GameState::capture(const Paletka& paddle,
    const Pilka& ball,
    const std::vector<Stone>& blocks)
{
    
    paddlePosition = sf::Vector2f(paddle.getX(), paddle.getY());

    
    ballPosition = sf::Vector2f(ball.getX(), ball.getY());

    
    ballVelocity = sf::Vector2f(ball.getVX(), ball.getVY());

    
    this->blocks.clear();
    this->blocks.reserve(blocks.size());

    for (const auto& b : blocks)
    {
        BlockData data;
        data.x = b.getPosition().x;
        data.y = b.getPosition().y;

        
        data.hp = b.isDestroyed() ? 0 : b.getHP();

        this->blocks.push_back(data);
    }
}

bool GameState::saveToFile(const std::string& nazwaPliku) const
{
    std::ofstream plik(nazwaPliku);
    if (!plik.is_open())
        return false;

    
    plik << "PADDLE " << paddlePosition.x << " " << paddlePosition.y << "\n";

    
    plik << "BALL " << ballPosition.x << " " << ballPosition.y << " "
        << ballVelocity.x << " " << ballVelocity.y << "\n";

    
    plik << "BLOCKS_COUNT " << blocks.size() << "\n";

    
    for (const auto& blok : blocks)
    {
        plik << blok.x << " " << blok.y << " " << blok.hp << "\n";
    }

    return true;
}

bool GameState::loadFromFile(const std::string& nazwaPliku)
{
    std::ifstream plik(nazwaPliku);
    if (!plik.is_open())
        return false;

    std::string etykieta;

    
    if (!(plik >> etykieta >> paddlePosition.x >> paddlePosition.y))
        return false;

    
    if (!(plik >> etykieta
        >> ballPosition.x >> ballPosition.y
        >> ballVelocity.x >> ballVelocity.y))
        return false;

    
    int liczbaBloków = 0;  
    if (!(plik >> etykieta >> liczbaBloków))
        return false;

    blocks.clear();
    blocks.reserve(static_cast<size_t>(liczbaBloków));

    for (int i = 0; i < liczbaBloków; ++i)
    {
        BlockData dane;
        if (!(plik >> dane.x >> dane.y >> dane.hp))
            return false;

        blocks.push_back(dane);
    }

    return true;
}

void GameState::apply(Paletka& paletka,
    Pilka& pilka,
    std::vector<Stone>& bloki) const
{
    
    paletka.setPosition(paddlePosition);

    
    pilka.reset(ballPosition, ballVelocity);

    
    sf::Vector2f rozmiarBloku(0.f, 0.f);
    if (!bloki.empty())
    {
        rozmiarBloku = bloki.front().getSize();
    }

    bloki.clear();
    bloki.reserve(blocks.size());

    for (const auto& dane : blocks)
    {
        
        if (dane.hp <= 0)
            continue;

        bloki.emplace_back(
            sf::Vector2f(dane.x, dane.y),
            rozmiarBloku,
            dane.hp
        );
    }
}
