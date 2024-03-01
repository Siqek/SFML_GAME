#include "stdafx.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font)
	: font(font)
{
	//Background
	this->background.setSize(sf::Vector2f(
		static_cast<float>(window.getSize().x),
		static_cast<float>(window.getSize().y)
	));
	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	//Container
	this->container.setSize(sf::Vector2f(
		static_cast<float>(window.getSize().x) / 4.f,
		static_cast<float>(window.getSize().y) - 120.f
	));
	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setPosition(
		static_cast<float>(window.getSize().x) / 2.f - this->container.getSize().x / 2.f,
		40.f
	);

	//Text
	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(255, 255, 255, 255));
	this->menuText.setCharacterSize(70);
	this->menuText.setString("PAUSED");
	this->menuText.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + 40.f);
}

PauseMenu::~PauseMenu()
{
	auto i = buttons.begin();

	for (i = buttons.begin(); i != buttons.end(); ++i)
	{
		delete i->second;
	}
}


//Accessors
std::map<std::string, gui::Button*>& PauseMenu::getButtons()
{
	return this->buttons;
}


//Functions
const bool PauseMenu::isButtonClicked(const std::string key)
{
	return this->buttons[key]->isClicked();
}

void PauseMenu::addButton(const std::string key, float pos_y, const std::string text)
{
	float width = 300.f;
	float hight = 70.f;
	float pos_x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;

	this->buttons[key] = new gui::Button(
		pos_x, pos_y, width, hight,
		&this->font, text, 40,
		sf::Color(100, 100, 100, 255), sf::Color(220, 220, 220, 255), sf::Color(50, 50, 50, 255),
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0)
	);
}

void PauseMenu::update(const sf::Vector2f& mousePos)
{
	for (auto &i : this->buttons)
	{
		i.second->update(mousePos);
	}
}

void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->container);

	for (auto &i : this->buttons)
	{
		i.second->render(target);
	}

	target.draw(this->menuText);
}
