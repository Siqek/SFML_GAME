#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include "State.h"
#include "Gui.h"
#include "PauseMenu.h"
#include "KeyboardEvents.h"
#include "TileMap.h"

class State;
class Gui;
class PauseManu;
class KeyboardEvents;
class TileMap;

class EditorState :
    public State
{
private:
    //Variables
    sf::Font font;
    sf::Text cursonText;
    PauseMenu* pmenu;
    KeyboardEvents* keyboardEvents;

    std::map<std::string, gui::Button*> buttons;

    TileMap* tileMap;

    sf::IntRect textureRect;
    sf::RectangleShape selectorRect;

    gui::TextureSelector* textureSelector;

    //Functions
    void initializeVariables();
    void initializeBackground();
    void initializeFonts();
    void initializeText();
    void initializeKeybinds();
    void initializePauseMenu();
    void initializeKeyboardEvents();
    void initializeButtons();
    void initializeTileMap();
    void initializeGui();

public:
    EditorState(StateData* state_data);
    virtual ~EditorState();

    //Functions

    //Update
    void updateInput(const float& dt);
    void updateEditorInput();
    void updateButtons();
    void updateGui();
    void updatePauseMenuButtons();
    void update(const float& dt);

    //Render
    void renderButtons(sf::RenderTarget& target);
    void renderGui(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);
};

#endif
