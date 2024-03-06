#include "stdafx.h"
#include "GameState.h"

//Initializer functions
void GameState::initializeKeybinds()
{
	/*Read keybinds from file and set them to variable*/
	std::ifstream ifs("Config/gamestate_keybinds.ini");

    if (ifs.is_open())
    {
        std::string functionality = "";
        std::string key = "";

        while (ifs >> functionality >> key)
        {
            this->keybinds[functionality] = this->supportedKeys->at(key);
        }
    }

    ifs.close();
}

void GameState::initializeFont()
{
	if (!this->font.loadFromFile("Fonts/SimplyMono.ttf"))
	{
		throw("ERROR::GAMESTATE::COULD NOT LOAD FONT");
	}
}

void GameState::initializeTextures()
{
	if (!this->textures["PLAYER_IDLE_SHEET"].loadFromFile("Resources/Images/Sprites/Player/Suss.png"))
	{
		throw("ERROR::GAMESTATE::COULD NOT LOAD PLAYER IDLE TEXTURE");
	}

	if (!this->textures["PLAYER_WALK_SHEET"].loadFromFile("Resources/Images/Sprites/Player/Sus.png"))
	{
		throw("ERROR::GAMESTATE::COULD NOT LOAD PLAYER WALK SHEET");
	}

	if (!this->textures["PLAYER_ATTACK_SHEET"].loadFromFile("Resources/Images/Sprites/Player/Attack.png"))
	{
		throw("ERROR::GAMESTATE::COULD NOT LOAD PLAYER ATTACK SHEET");
	}
}

void GameState::initializePauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);

	this->pmenu->addButton("QUIT", 820.f, "Quit");
}

void GameState::initializeKeyboardEvents()
{
	this->keyboardEvents = new KeyboardEvents(&this->keybinds);
}

void GameState::initializePlayers()
{
	this->player = new Player(0.f, 0.f, this->textures);
}

void GameState::initializeTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 12, 12);
}


//Constructor/Destructor
GameState::GameState(StateData* state_data)
	: State(state_data)
{
	this->initializeKeybinds();
	this->initializeFont();
	this->initializeTextures();
	this->initializePauseMenu();
	this->initializeKeyboardEvents();
	this->initializePlayers();
	this->initializeTileMap();
}

GameState::~GameState()
{
	delete this->pmenu;
	delete this->keyboardEvents;
	delete this->player;
	delete this->tileMap;
}


void GameState::updateInput(const float& dt)
{
	if (!this->window->hasFocus())
	{
		this->pauseState();
	}
	else if (this->keyboardEvents->isKeyDown("CLOSE"))
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void GameState::updatePlayerInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->player->move(-1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->player->move(1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
		this->player->move(0.f, -1.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
		this->player->move(0.f, 1.f, dt);
}

void GameState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonClicked("QUIT"))
		this->endState();
}

void GameState::update(const float& dt)
{
	this->updateMousePositions();
	this->keyboardEvents->updateKeysStatus();
	//this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->paused) //Unpaused
	{
		this->updatePlayerInput(dt);

		this->player->update(dt);
	}
	else //Paused
	{
		this->pmenu->update(this->mousePosView);
		this->updatePauseMenuButtons();
	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	//this->map->render(*target);

	this->player->render(*target);

	if (this->paused) //Pause menu render
	{
		this->pmenu->render(*target);
	}
}
