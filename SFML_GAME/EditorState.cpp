#include "stdafx.h"
#include "EditorState.h"

//Initializer functions
void EditorState::initializeVariables()
{
	this->textureRect = sf::IntRect(0, 0, static_cast<int>(this->stateData->gridSize), static_cast<int>(this->stateData->gridSize));
}

void EditorState::initializeBackground()
{

}

void EditorState::initializeFonts()
{
	if (!this->font.loadFromFile("Fonts/ARIAL.ttf"))
	{
		throw("ERROR::EDITORSTATE::COULD NOT LOAD FONT");
	}
}

void EditorState::initializeKeybinds()
{
	std::ifstream ifs("config/editorstate_keybinds.ini");

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

void EditorState::initializePauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);

	this->pmenu->addButton("QUIT", 820.f, "Quit");
}

void EditorState::initializeKeyboardEvents()
{
	this->keyboardEvents = new KeyboardEvents(&this->keybinds);
}

void EditorState::initializeButtons()
{

}

void EditorState::initializeGui()
{
	this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));
	this->selectorRect.setPosition(0.f, 0.f);

	this->selectorRect.setFillColor(sf::Color::Transparent);
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::Red);
}

void EditorState::initializeTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 12, 12);
}


EditorState::EditorState(StateData* state_data)
	: State(state_data)
{
	this->initializeVariables();
	this->initializeBackground();
	this->initializeFonts();
	this->initializeKeybinds();
	this->initializePauseMenu();
	this->initializeKeyboardEvents();
	this->initializeButtons();
	this->initializeGui();
	this->initializeTileMap();
}

EditorState::~EditorState()
{
	auto i = buttons.begin();

	for (i = buttons.begin(); i != buttons.end(); ++i)
	{
		delete i->second;
	}

	delete this->keyboardEvents;

	delete this->pmenu;

	delete this->tileMap;
}


//Functions
void EditorState::updateInput(const float& dt)
{
	if (!this->window->hasFocus())
	{
		this->pauseState();
	}
	else if (this->keyboardEvents->isWaspressed("CLOSE"))
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void EditorState::updateEditorInput()
{
	//Add a tile
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->textureRect);
	}
	//Remove a tile
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
	}

	//Change texture
	if (this->keyboardEvents->isWaspressed("CHANGE_TEXTURE"))
	{
		if (this->textureRect.left < 64)
			this->textureRect.left += 64;
		else
			this->textureRect.left -= 64;
	}

	if (this->keyboardEvents->isWaspressed("CHANGE_TEXTURE_2"))
	{
		if (this->textureRect.top < 64)
			this->textureRect.top += 64;
		else
			this->textureRect.top -= 64;
	}
}

void EditorState::updateButtons()
{
	/*Update all the buttons in the state and handle their functionality*/
	for (auto& i : this->buttons)
	{
		i.second->update(this->mousePosView);
	}
}

void EditorState::updateGui()
{
	this->selectorRect.setPosition(this->mousePosGrid.x * this->stateData->gridSize, this->mousePosGrid.y * this->stateData->gridSize);
}

void EditorState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonClicked("QUIT"))
		this->endState();
}

void EditorState::update(const float& dt)
{
	this->updateMousePositions();
	this->keyboardEvents->updateKeysStatus();
	this->updateInput(dt);

	if (!this->paused) //Unpaused
	{
		this->updateButtons();
		this->updateGui();
		this->updateEditorInput();
	}
	else //Paused
	{
		this->pmenu->update(this->mousePosView);
		this->updatePauseMenuButtons();
	}
}

void EditorState::renderButtons(sf::RenderTarget& target)
{
	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}
}

void EditorState::renderGui(sf::RenderTarget& target)
{
	target.draw(this->selectorRect);
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->renderButtons(*target);
	this->renderGui(*target);

	this->tileMap->render(*target);

	if (this->paused) //Pause menu render
	{
		this->pmenu->render(*target);
	}


	//DELETE THIS!!!!
	//to finding where you want set buttons, only debug
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x + 20, this->mousePosView.y);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(14);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y << std::endl << this->textureRect.left << " " << this->textureRect.top;
	mouseText.setString(ss.str());
	target->draw(mouseText);
}