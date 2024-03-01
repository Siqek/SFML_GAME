#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{

}

Tile::Tile(float x, float y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect)
{
	this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->shape.setFillColor(sf::Color(255, 255, 255, 255)); //70, 255, 70, 50
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(sf::Color(0, 0, 0, 127));
	this->shape.setPosition(x, y);
	this->shape.setTexture(&texture);
	this->shape.setTextureRect(texture_rect);
}

Tile::~Tile()
{

}


//Functions
void Tile::update()
{

}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
