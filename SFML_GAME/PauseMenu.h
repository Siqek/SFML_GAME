#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "Gui.h"

class PauseMenu
{
private:
	//Variables
	sf::Font& font;
	sf::Text menuText;

	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map<std::string, gui::Button*> buttons;

public:
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	virtual ~PauseMenu();

	//Accessors
	std::map<std::string, gui::Button*>& getButtons();

	//Functions
	const bool isButtonClicked(const std::string key);
	void addButton(const std::string key, float pos_y, const std::string text);
	void update(const sf::Vector2f& mousePos);
	void render(sf::RenderTarget& target);
};

#endif
