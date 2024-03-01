#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H

#include "State.h"
#include "Gui.h"

class SettingsState :
	public State
{
private:
    //Variables
    sf::Texture backgroundTexture;
    sf::RectangleShape backgroud;
    sf::Font font;

    std::map<std::string, gui::Button*> buttons;
    std::map<std::string, gui::DropDownList*> dropDownLists;

    sf::Text optionsText;

    std::vector<sf::VideoMode> modes;

    //Functions
    void initializeVariables();
    void initializeBackground();
    void initializeFonts();
    void initializeKeybinds();
    void initializeGui();
    void initializeText();

public:
	SettingsState(StateData* state_data);
	virtual ~SettingsState();

	//Accessors

	//Functions
    
    //Update
    void updateInput(const float& dt);
    void updateGui(const float& dt);
    void update(const float& dt);

    //Render
    void renderGui(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);
};

#endif
