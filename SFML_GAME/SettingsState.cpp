#include "stdafx.h"
#include "SettingsState.h"

//Initializer functions
void SettingsState::initializeVariables()
{
	this->modes = sf::VideoMode::getFullscreenModes();
}

void SettingsState::initializeBackground()
{
	this->backgroud.setSize(sf::Vector2f(static_cast<sf::Vector2f>(this->window->getSize())));

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/BackgroundTest.png"))
	{
		throw("ERROR::MAINMENUSTATE::FAILED TO LOAD BACKGROUND TEXTURE");
	}

	this->backgroud.setTexture(&this->backgroundTexture);
}

void SettingsState::initializeFonts()
{
	if (!this->font.loadFromFile("Fonts/Arial.ttf"))
	{
		throw("ERROR::MAINMANUSTATE::COULD NOT LOAD FONT");
	}
}

void SettingsState::initializeKeybinds()
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

void SettingsState::initializeGui()
{
	this->buttons["BACK"] = new gui::Button(1500.f, 750.f, 200.f, 100.f,
		&this->font, "Back", 40,
		sf::Color(100, 100, 100, 255), sf::Color(220, 220, 220, 255), sf::Color(50, 50, 50, 255),
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0));

	this->buttons["APPLY"] = new gui::Button(1200.f, 750.f, 200.f, 100.f,
		&this->font, "Apply", 40,
		sf::Color(100, 100, 100, 255), sf::Color(220, 220, 220, 255), sf::Color(50, 50, 50, 255),
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0));

	std::vector<std::string> modes_str;
	for (auto &i : this->modes)
	{
		modes_str.push_back(std::to_string(i.width) + "x" + std::to_string(i.height));
	}

	this->dropDownLists["RESOLUTION"] = new gui::DropDownList(400.f, 100.f, 200.f, 50.f, this->font, modes_str.data(), modes_str.size());
}

void SettingsState::initializeText()
{
	this->optionsText.setFont(this->font);
	this->optionsText.setPosition(sf::Vector2f(100.f, 100.f));
	this->optionsText.setCharacterSize(25);
	this->optionsText.setFillColor(sf::Color(255, 255, 255, 255));

	this->optionsText.setString("Resolution \nVsync");
}


SettingsState::SettingsState(StateData* state_data)
	: State(state_data)
{
	this->initializeVariables();
	this->initializeBackground();
	this->initializeFonts();
	this->initializeKeybinds();
	this->initializeGui();
	this->initializeText();
}

SettingsState::~SettingsState()
{
	auto i = buttons.begin();

	for (i = buttons.begin(); i != buttons.end(); ++i)
	{
		delete i->second;
	}

	auto i2 = dropDownLists.begin();

	for (i2 = dropDownLists.begin(); i2 != dropDownLists.end(); ++i2)
	{
		delete i2->second;
	}
}


//Accessors

//Functions
void SettingsState::updateInput(const float& dt)
{

}

void SettingsState::updateGui(const float& dt)
{
	/*Update all the gui elements in the state and handle their functionality*/

	//Buttons
	for (auto& i : this->buttons)
	{
		i.second->update(this->mousePosView);
	}

	//Buttons functionality
	//Back to MainMenuState
	if (this->buttons["BACK"]->isClicked())
	{
		this->quit = true;
	}

	//Apply selected settings
	if (this->buttons["APPLY"]->isClicked())
	{
		this->stateData->gfxSettings->resolution = this->modes[this->dropDownLists["RESOLUTION"]->getActiveElementId()];
		this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, sf::Style::Default);
	}

	//DropDownLists
	for (auto& i : this->dropDownLists)
	{
		i.second->update(this->mousePosView, dt);
	}

	//DropDownLists functionality
}

void SettingsState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateGui(dt);
}

void SettingsState::renderGui(sf::RenderTarget& target)
{
	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}

	for (auto& i : this->dropDownLists)
	{
		i.second->render(target);
	}
}

void SettingsState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->backgroud);

	this->renderGui(*target);

	target->draw(this->optionsText);

	//DELETE THIS!!!!
	//to finding where you want set buttons, only debug
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x + 20, this->mousePosView.y);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(14);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);
}