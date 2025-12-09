#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>

#include "Game.h"
#include "Menu.h"

enum class AppState { Menu, Playing, Scores, Exiting };

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Arkanoid");
    window.setFramerateLimit(60);

    Menu menu(window.getSize().x, window.getSize().y);
    Game game;

    AppState currentState = AppState::Menu;

    sf::Clock deltaClock;

    
    sf::Font fontWynikow;
    if (!fontWynikow.loadFromFile("arial.ttf"))
    {
        std::cout << "Blad ladowania czcionki arial.ttf (wyniki)\n";
    }

    std::vector<int> ostatnieWyniki;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                currentState = AppState::Exiting;
                window.close();
            }

            if (event.type == sf::Event::KeyPressed)
            {
                
                if (currentState == AppState::Menu)
                {
                    if (event.key.code == sf::Keyboard::Up)
                    {
                        menu.przesunG();
                    }
                    else if (event.key.code == sf::Keyboard::Down)
                    {
                        menu.przesunD();
                    }
                    else if (event.key.code == sf::Keyboard::Enter)
                    {
                        int selected = menu.getSelectedItem();

                        if (selected == 0)
                        {
                            
                            game.zresetujGre(); 
                            currentState = AppState::Playing;
                        }

                        else if (selected == 1)
                        {
                            
                            if (!game.wczytajGre("zapis.txt"))
                            {
                                std::cout << "Nie udalo sie wczytac zapis.txt\n";
                            }
                            currentState = AppState::Playing;
                        }
                        else if (selected == 2)
                        {
                            
                            ostatnieWyniki.clear();

                            std::ifstream plikWyniki("wyniki.txt");
                            if (plikWyniki.is_open())
                            {
                                int pojedynczyWynik = 0;
                                while (plikWyniki >> pojedynczyWynik)
                                {
                                    ostatnieWyniki.push_back(pojedynczyWynik);
                                }
                            }
                            else
                            {
                                std::cout << "Brak pliku wyniki.txt lub nie mozna otworzyc\n";
                            }

                            currentState = AppState::Scores;
                        }
                        else if (selected == 3)
                        {
                            
                            currentState = AppState::Exiting;
                            window.close();
                        }
                    }
                }
                
                else if (currentState == AppState::Playing)
                {
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        
                        currentState = AppState::Menu;
                    }
                    else if (event.key.code == sf::Keyboard::S)
                    {
                        
                        if (!game.zapiszGre("zapis.txt"))
                        {
                            std::cout << "Nie udalo sie zapisac do zapis.txt\n";
                        }
                    }
                }
                
                else if (currentState == AppState::Scores)
                {
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        
                        currentState = AppState::Menu;
                    }
                }
            }
        }

        
        sf::Time dt = deltaClock.restart();
        if (currentState == AppState::Playing)
        {
            game.update(dt);
        }

        
        window.clear(sf::Color(20, 20, 20));

        if (currentState == AppState::Menu)
        {
            menu.draw(window);
        }
        else if (currentState == AppState::Playing)
        {
            game.render(window);
        }
        else if (currentState == AppState::Scores)
        {
            

            sf::Text tytul;
            tytul.setFont(fontWynikow);
            tytul.setString("Ostatnie wyniki");
            tytul.setCharacterSize(32);
            tytul.setFillColor(sf::Color::Cyan);
            tytul.setPosition(200.f, 50.f);
            window.draw(tytul);

            if (ostatnieWyniki.empty())
            {
                sf::Text brak;
                brak.setFont(fontWynikow);
                brak.setString("Brak zapisanych wynikow.\nZagraj, aby zapisac wynik.");
                brak.setCharacterSize(20);
                brak.setFillColor(sf::Color::White);
                brak.setPosition(200.f, 150.f);
                window.draw(brak);
            }
            else
            {
                float pozycjaY = 150.f;
                int maksymalnaLiczbaWynikow = 10; 
                int licznikWyswietlonych = 0;

                
                for (int i = static_cast<int>(ostatnieWyniki.size()) - 1;
                    i >= 0 && licznikWyswietlonych < maksymalnaLiczbaWynikow;
                    --i)
                {
                    sf::Text tekstWyniku;
                    tekstWyniku.setFont(fontWynikow);
                    tekstWyniku.setCharacterSize(24);
                    tekstWyniku.setFillColor(sf::Color::White);

                    tekstWyniku.setString(
                        std::to_string(licznikWyswietlonych + 1) + ". " +
                        std::to_string(ostatnieWyniki[i])
                    );
                    tekstWyniku.setPosition(250.f, pozycjaY);
                    window.draw(tekstWyniku);

                    pozycjaY += 30.f;
                    ++licznikWyswietlonych;
                }

                sf::Text podpowiedz;
                podpowiedz.setFont(fontWynikow);
                podpowiedz.setCharacterSize(18);
                podpowiedz.setFillColor(sf::Color(160, 160, 160));
                podpowiedz.setString("Wcisnij ESC, aby wrocic do menu");
                podpowiedz.setPosition(200.f, 500.f);
                window.draw(podpowiedz);
            }
        }

        window.display();
    }

    return 0;
}
