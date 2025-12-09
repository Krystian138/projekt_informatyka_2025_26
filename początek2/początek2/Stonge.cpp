#include "Stonge.h"


Stone::Stone(sf::Vector2f startPos, sf::Vector2f rozmiar, int L)
{
	m_punktyZycia = L;
	m_jestZniszczony = false;

	this->setPosition(startPos);
	this->setSize(rozmiar);
	setOutlineThickness(2.f);
	aktualizujKolor();
}

void Stone::trafienie() {
	if (m_jestZniszczony == true)
	{
		return;
	}
	m_punktyZycia = m_punktyZycia - 1;
	aktualizujKolor();
	if (m_punktyZycia <= 0)
	{
		m_jestZniszczony = true;
	}

}

void Stone::aktualizujKolor() { 

	int idx = m_punktyZycia;

	
	if (idx < 0)
		idx = 0;
	if (idx >= static_cast<int>(m_colorLUT.size()))
		idx = static_cast<int>(m_colorLUT.size()) - 1;

	this->setFillColor(m_colorLUT[idx]);
}



bool Stone::isDestroyed() const {
	return m_jestZniszczony;
};


void Stone::draw(sf::RenderTarget& target) const {
	if (isDestroyed() == false)
	{
		target.draw(*this);
	}

}

const std::array<sf::Color, 4> Stone::m_colorLUT = {
	sf::Color::Transparent,
	sf::Color::Red,
	sf::Color::Yellow,
	sf::Color::Blue
};