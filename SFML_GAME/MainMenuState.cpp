#include "stdafx.h"
#include "MainMenuState.h"

//Initializer functions
void MainMenuState::initializeVariables()
{

}

void MainMenuState::initializeBackground()
{
	this->backgroud.setSize(sf::Vector2f(static_cast<sf::Vector2f>(this->window->getSize())));

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/BackgroundTest.png"))
	{
		throw("ERROR::MAINMENUSTATE::FAILED TO LOAD BACKGROUND TEXTURE");
	}

	this->backgroud.setTexture(&this->backgroundTexture);
}

void MainMenuState::initializeFonts()
{
	if (!this->font.loadFromFile("Fonts/SimplyMono.ttf"))
	{
		throw("ERROR::MAINMANUSTATE::COULD NOT LOAD FONT");
	}
}

void MainMenuState::initializeKeybinds()
{
	std::ifstream ifs("config/mainmenustate_keybinds.ini");

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

void MainMenuState::initializeButtons()
{
	this->buttons["GAME_STATE"] = new gui::Button(200.f, 200.f, 300.f, 100.f,
		&this->font, "New game", 40,
		sf::Color(100, 100, 100, 255), sf::Color(220, 220, 220, 255), sf::Color(50, 50, 50, 255),
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0));

	this->buttons["SETTINGS_STATE"] = new gui::Button(200.f, 350.f, 300.f, 100.f,
		&this->font, "Settings", 40,
		sf::Color(100, 100, 100, 255), sf::Color(220, 220, 220, 255), sf::Color(50, 50, 50, 255),
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0));

	this->buttons["EDITOR_STATE"] = new gui::Button(200.f, 500.f, 300.f, 100.f,
		&this->font, "Editor", 40,
		sf::Color(100, 100, 100, 255), sf::Color(220, 220, 220, 255), sf::Color(50, 50, 50, 255),
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0));

	this->buttons["EXIT_STATE"] = new gui::Button(200.f, 750.f, 300.f, 100.f,
		&this->font, "Quit", 40,
		sf::Color(100, 100, 100, 255), sf::Color(220, 220, 220, 255), sf::Color(50, 50, 50, 255),
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0));
}


MainMenuState::MainMenuState(StateData* state_data)
	: State(state_data)
{
	this->initializeVariables();
	this->initializeBackground();
	this->initializeFonts();
	this->initializeKeybinds();
	this->initializeButtons();
}

MainMenuState::~MainMenuState()
{
	auto i = buttons.begin();

	for (i = buttons.begin(); i != buttons.end(); ++i)
	{
		delete i->second;
	}
}


void MainMenuState::updateInput(const float& dt)
{
	
}

void MainMenuState::updateButtons()
{
	/*Update all the buttons in the state and handle their functionality*/
	for (auto& i : this->buttons)
	{
		i.second->update(this->mousePosView);
	}

	//New game
	if (this->buttons["GAME_STATE"]->isClicked())
	{
		//Push GameState to states
		this->states->push(new GameState(this->stateData));
	}

	//Settings
	if (this->buttons["SETTINGS_STATE"]->isClicked())
	{
		//Push SettingsState to states
		this->states->push(new SettingsState(this->stateData));
	}

	//Editor State
	if (this->buttons["EDITOR_STATE"]->isClicked())
	{
		//Push GameState to states
		this->states->push(new EditorState(this->stateData));
	}

	//Quit the game
	if (this->buttons["EXIT_STATE"]->isClicked())
	{
		this->quit = true;
	}
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->backgroud);

	this->renderButtons(*target);


	//DELETE THIS!!!!
	//to finding where you want set buttons, only debug
	/*sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x + 20, this->mousePosView.y);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(14);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);*/
}