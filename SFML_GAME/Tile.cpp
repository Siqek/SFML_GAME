#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{
	this->collision = false;
	this->type = TileTypes::DEAFULT;
}

Tile::Tile(unsigned grid_x, unsigned grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect,
	bool collision, short type)
{
	this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->shape.setFillColor(sf::Color(255, 255, 255, 255)); //70, 255, 70, 50
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(sf::Color(0, 0, 0, 127));
	this->shape.setPosition(static_cast<float>(grid_x) * gridSizeF, static_cast<float>(grid_y) * gridSizeF);
	this->shape.setTexture(&texture);
	this->shape.setTextureRect(texture_rect);

	this->collision = collision;
	this->type = type;
}

Tile::~Tile()
{

}


//Functions
const std::string Tile::getAsString() const
{
	std::stringstream ss;

	ss << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " " << this->collision << " " << this->type;

	return ss.str();
}

void Tile::update()
{

}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
