#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"

#include "KeyboardEvents.h"

class GameState :
    public State
{
private:
    sf::Font font;

    PauseMenu* pmenu;
    KeyboardEvents* keyboardEvents;

    Player* player;

    TileMap* tileMap;

    //Functions
    void initializeKeybinds();
    void initializeFont();
    void initializeTextures();
    void initializePauseMenu();
    void initializeKeyboardEvents();
    void initializePlayers();
    void initializeTileMap();

public:
    GameState(StateData* state_data);
    virtual ~GameState();

    //Functions

    //Update
    void updateInput(const float& dt);
    void updatePlayerInput(const float& dt);
    void updatePauseMenuButtons();
    void update(const float& dt);

    //Render
    void render(sf::RenderTarget* target = nullptr);
};


#endif
