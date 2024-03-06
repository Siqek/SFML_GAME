#include "stdafx.h"
#include "Gui.h"

gui::TextureSelector::TextureSelector(float x, float y, float height, float width, const sf::Texture* texture_sheet)
{
	this->bounds.setSize(sf::Vector2f(width, height));
	this->bounds.setPosition(x, y);
	this->bounds.setFillColor(sf::Color(40, 40, 40, 120));
	this->bounds.setOutlineThickness(1.f);
	this->bounds.setOutlineColor(sf::Color(255, 255, 255, 150));

	this->sheet.setTexture(*texture_sheet);
	this->sheet.setPosition(x, y);

	if (this->sheet.getGlobalBounds().width > this->bounds.getGlobalBounds().width)
	{
		this->sheet.setTextureRect(sf::IntRect(0, 0, this->bounds.getGlobalBounds().width, this->sheet.getGlobalBounds().height));
	}
	if (this->sheet.getGlobalBounds().height > this->bounds.getGlobalBounds().height)
	{
		this->sheet.setTextureRect(sf::IntRect(0, 0, this->sheet.getGlobalBounds().width, this->bounds.getGlobalBounds().height));
	}
}

gui::TextureSelector::~TextureSelector()
{

}


//Functions
void gui::TextureSelector::update()
{

}

void gui::TextureSelector::render(sf::RenderTarget& target)
{
	target.draw(this->bounds);
	target.draw(this->sheet);
}
