#ifndef STATE_H
#define STATE_H

#include "Player.h"
#include "GraphicsSettings.h"

class Player;
class GraphicsSettings;
class State;

class StateData
{
public:
	StateData() 
	{
		this->gridSize = NULL;
		this->window = nullptr;
		this->gfxSettings = nullptr;
		this->supportedKeys = nullptr;
		this->states = nullptr;
	}

	//Variables
	float gridSize;
	sf::RenderWindow* window;
	GraphicsSettings* gfxSettings;
	std::map < std::string, int >* supportedKeys;
	std::stack<State*>* states;

	//Funcions
};

class State
{
private:


protected:
	//Variables
	StateData* stateData;
	std::stack<State*>* states;
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	bool quit;
	bool paused;
	float keytime;
	float keytimeMax;
	float gridSize;

	//Mouse positions
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2u mousePosGrid;

	//Resources
	std::map<std::string, sf::Texture> textures;

	//Functions
	virtual void initializeKeybinds() = 0;

public:
	State(StateData* state_data);
	virtual ~State();

	//Accessors
	const bool& getQuit() const;
	const bool getKeytime();

	//Functions
	
	//State
	void endState();
	void pauseState();
	void unpauseState();

	//Update
	virtual void updateMousePositions(); //virtual functions (if not defined, use base class functions)
	virtual void updateKeytime(const float& dt);
	virtual void updateInput(const float& dt) = 0; //pure virtual function (force definition in child classes)
	virtual void update(const float& dt) = 0;

	//Render
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

#endif
