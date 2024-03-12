#include "stdafx.h"
#include "Game.h"

//Static functions

void Game::initializeVariables()
{
    this->window = nullptr;

    this->dt = 0.f;

    this->gridSize = 64.f;
}

void Game::initializeGraphicsSettings()
{
    this->gfxSettings.loadFromFile("Config\\graphics.ini");
}

//Initializer functions
void Game::initializeWindow()
{
    /*Create SFML window*/

    if (this->gfxSettings.fullscreen)
        this->window = new sf::RenderWindow(
            this->gfxSettings.resolution,
            this->gfxSettings.title,
            sf::Style::Fullscreen, 
            this->gfxSettings.constextSettings);
    else
        this->window = new sf::RenderWindow(
            this->gfxSettings.resolution,
            this->gfxSettings.title, 
            sf::Style::Titlebar | sf::Style::Close,
            this->gfxSettings.constextSettings);

    this->window->setFramerateLimit(this->gfxSettings.frameRateLimit);
    this->window->setVerticalSyncEnabled(this->gfxSettings.verticalSync);
}

void Game::initializeKeys()
{
    std::ifstream ifs("Config/supported_keys.ini");

    if (ifs.is_open())
    {
        std::string key = "";
        int key_value = 0;

        while (ifs >> key >> key_value)
        {
            this->supportedKeys[key] = key_value;
        }
    }

    ifs.close();
}

void Game::initializeStateData()
{
    this->stateData.window = this->window;
    this->stateData.gfxSettings = &this->gfxSettings;
    this->stateData.supportedKeys = &this->supportedKeys;
    this->stateData.states = &this->states;
    this->stateData.gridSize = this->gridSize;
}

void Game::initializeStates()
{
    this->states.push(new MainMenuState(&this->stateData));
}


//Constructors/Destractors
Game::Game()
{
    this->initializeVariables();
    this->initializeGraphicsSettings();
    this->initializeWindow();
    this->initializeKeys();
    this->initializeStateData();
    this->initializeStates();
}

Game::~Game()
{
	delete this->window;

    while (!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }
}


//Functions

void Game::endApplication()
{
    std::cout << "Ending Application!" << std::endl;
}

void Game::updateDeltaTime()
{
    this->dt = this->dtClock.restart().asSeconds();

}

void Game::updateSFMLEvents()
{
    while (this->window->pollEvent(this->sfEvent))
    {
        if (this->sfEvent.type == sf::Event::Closed) //sprawdzenie czy user chce zamkn¹æ okno
            this->window->close(); //zamkniêcie okna  
    }
}

void Game::update()
{
    this->updateSFMLEvents();

    if (!this->states.empty())
    {
        this->states.top()->update(this->dt);

        if (this->states.top()->getQuit())
        {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    }
    //End of application
    else
    {
        this->endApplication();
        this->window->close();
    }
}

void Game::render()
{
    this->window->clear();

    //Render items
    if (!this->states.empty())
        this->states.top()->render();

    this->window->display();
}

void Game::run()
{
    while (this->window->isOpen()) //Game loop
    {
        this->updateDeltaTime();
        this->update();
        this->render();
    }
}
