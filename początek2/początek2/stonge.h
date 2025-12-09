#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <array> 

class Stone : public sf::RectangleShape
{
public:
	Stone(sf::Vector2f startPos, sf::Vector2f rozmiar, int L);
	void trafienie();
	void aktualizujKolor();

	void draw(sf::RenderTarget& target) const;
	bool isDestroyed() const;

	int getHP() const { return m_punktyZycia; }

private:
	int m_punktyZycia;
	bool m_jestZniszczony;
	static const std::array<sf::Color, 4> m_colorLUT;
};




