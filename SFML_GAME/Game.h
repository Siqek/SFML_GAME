#ifndef GAME_H
#define GAME_H

#include "MainMenuState.h"

class Game
{
private:
	//Variables
	GraphicsSettings gfxSettings;
	StateData stateData;
	sf::RenderWindow *window;
	sf::Event sfEvent;

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

	float gridSize;

	//Initialization
	void initializeVariables();
	void initializeGraphicsSettings();
	void initializeWindow();
	void initializeKeys();
	void initializeStateData();
	void initializeStates();

public:
	//Construstors/Destructors
	Game();
	virtual ~Game();

	//Functions
	void endApplication();
	void updateDeltaTime();
	void updateSFMLEvents();
	void update();
	void render();
	void run();
};


#endif