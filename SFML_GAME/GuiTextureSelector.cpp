#include "stdafx.h"
#include "Gui.h"

gui::TextureSelector::TextureSelector(float x, float y, float height, float width, float gridSize, const sf::Texture* texture_sheet)
{
	this->gridSize = gridSize;
	this->active = false;

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

	this->selector.setPosition(x, y);
	this->selector.setSize(sf::Vector2f(gridSize, gridSize));
	this->selector.setFillColor(sf::Color::Transparent);
	this->selector.setOutlineThickness(1.f);
	this->selector.setOutlineColor(sf::Color::Green);

	this->textureRect.width = static_cast<int>(gridSize);
	this->textureRect.height = static_cast<int>(gridSize);
}

gui::TextureSelector::~TextureSelector()
{

}


//Accessors
const bool& gui::TextureSelector::getActive() const
{
	return this->active;
}

const sf::IntRect& gui::TextureSelector::getTextureRect() const
{
	return this->textureRect;
}

//Functions
void gui::TextureSelector::update(const sf::Vector2i& mousePosWindow)
{
	if (this->bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
		this->active = true;
	else
		this->active = false;

	if (this->active)
	{
		this->mousePosGrid.x = (mousePosWindow.x - static_cast<int>(this->bounds.getPosition().x)) / static_cast<unsigned>(this->gridSize);
		this->mousePosGrid.y = (mousePosWindow.y - static_cast<int>(this->bounds.getPosition().y)) / static_cast<unsigned>(this->gridSize);

		this->selector.setPosition(
			this->bounds.getPosition().x + this->mousePosGrid.x * this->gridSize,
			this->bounds.getPosition().y + this->mousePosGrid.y * this->gridSize
		);

		//Update texture rectangle
		this->textureRect.left = this->mousePosGrid.x * this->gridSize;
		this->textureRect.top = this->mousePosGrid.y * this->gridSize; //static_cast<int>(this->selector.getPosition().y - this->bounds.getPosition().y);
	}
}

void gui::TextureSelector::render(sf::RenderTarget& target)
{
	target.draw(this->bounds);
	target.draw(this->sheet);

	if (this->active)
		target.draw(this->selector);
}
