#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"
#include "EditorState.h"
#include "SettingsState.h"
#include "Gui.h"

class MainMenuState :
    public State
{
private:
    //Variables
    sf::RectangleShape backgroud;
    sf::Font font;

    std::map<std::string, gui::Button*> buttons;

    //Resources
    sf::Texture backgroundTexture;

    //Functions
    void initializeVariables();
    void initializeBackground();
    void initializeFonts();
    void initializeKeybinds();
    void initializeButtons();

public:
    MainMenuState(StateData* state_data);
    virtual ~MainMenuState();

    //Functions

    //Update
    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);

    //Render
    void renderButtons(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);
};

#endif