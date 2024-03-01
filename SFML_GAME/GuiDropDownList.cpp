#include "stdafx.h"
#include "Gui.h"

gui::DropDownList::DropDownList(float pos_x, float pos_y, float width, float height,
	sf::Font& font, std::string list[],
	unsigned numOfElements, unsigned defult_index)
	: font(font), showList(false), keytimeMax(1.f), keytime(1.f)
{
	//unsigned numOfElements = sizeof(list) / sizeof(std::string);

	this->activeElement = new gui::Button(
		pos_x, pos_y, width, height,
		&this->font, list[defult_index], 20,
		sf::Color(100, 100, 100, 255), sf::Color(220, 220, 220, 255), sf::Color(50, 50, 50, 255),
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(100, 100, 100, 255), sf::Color(220, 220, 220, 255), sf::Color(50, 50, 50, 255)
	);

	for (size_t i = 0; i < numOfElements; i++)
	{
		this->list.push_back(
			new gui::Button(
				pos_x, pos_y + ((i + 1) * height), width, height,
				&this->font, list[i], 20,
				sf::Color(100, 100, 100, 255), sf::Color(220, 220, 220, 255), sf::Color(50, 50, 50, 255),
				sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
				sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent,
				i
			)
		);
	}
}

gui::DropDownList::~DropDownList()
{
	delete this->activeElement;

	for (size_t i = 0; i < this->list.size(); i++)
	{
		delete this->list[i];
	}
}


//Accessors
const bool gui::DropDownList::getKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}

	return false;
}

const unsigned short& gui::DropDownList::getActiveElementId() const
{
	return this->activeElement->getId();
}

//Functions
void gui::DropDownList::updateKeytime(const float& dt)
{
	if (this->keytime < this->keytimeMax)
		this->keytime += 10.f * dt;
}

void gui::DropDownList::update(const sf::Vector2f& mousePos, const float& dt)
{
	this->updateKeytime(dt);

	this->activeElement->update(mousePos);

	//Show/Hide list
	if (this->activeElement->isClicked())
	{
		if (this->showList)
			this->showList = false;
		else
			this->showList = true;
	}

	if (this->showList)
	{
		for (auto& i : this->list)
		{
			i->update(mousePos);

			if (i->isClicked())
			{
				this->showList = false;
				this->activeElement->setText(i->getText());
				this->activeElement->setId(i->getId());
			}
		}
	}
}

void gui::DropDownList::render(sf::RenderTarget& target)
{
	this->activeElement->render(target);

	if (this->showList)
	{
		for (auto& i : this->list)
		{
			i->render(target);
		}
	}
}
