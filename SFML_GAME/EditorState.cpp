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

void EditorState::initializeText()
{
	this->cursonText.setFont(this->font);
	this->cursonText.setFillColor(sf::Color::White);
	this->cursonText.setCharacterSize(14);
	this->cursonText.setPosition(this->mousePosView.x, this->mousePosView.y);
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
	this->pmenu->addButton("SAVE", 620.f, "Save");
	this->pmenu->addButton("LOAD", 520.f, "Load");
}

void EditorState::initializeKeyboardEvents()
{
	this->keyboardEvents = new KeyboardEvents(&this->keybinds);
}

void EditorState::initializeButtons()
{

}

void EditorState::initializeTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 12, 12, "Resources\\Images\\Tiles\\tilesheet.png");
}

void EditorState::initializeGui()
{
	this->sidebar.setSize(sf::Vector2f(100.f, static_cast<float>(this->stateData->gfxSettings->resolution.height)));
	this->sidebar.setFillColor(sf::Color(100, 100, 100, 40));
	this->sidebar.setOutlineThickness(1.f);
	this->sidebar.setOutlineColor(sf::Color(200, 200, 200, 40));

	this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));
	this->selectorRect.setPosition(0.f, 0.f);

	this->selectorRect.setFillColor(sf::Color(255, 255, 255, 180));
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::Red);

	this->selectorRect.setTexture(this->tileMap->getTileSheet());
	this->selectorRect.setTextureRect(this->textureRect);

	this->textureSelector = new gui::TextureSelector(30.f, 10.f, 400.f, 400.f, 
		this->stateData->gridSize, this->tileMap->getTileSheet(),
		this->font, "HIDE");
}


EditorState::EditorState(StateData* state_data)
	: State(state_data)
{
	this->initializeVariables();
	this->initializeBackground();
	this->initializeFonts();
	this->initializeText();
	this->initializeKeybinds();
	this->initializePauseMenu();
	this->initializeKeyboardEvents();
	this->initializeButtons();
	this->initializeTileMap();
	this->initializeGui();
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

	delete this->textureSelector;
}


//Functions
void EditorState::updateInput(const float& dt)
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

void EditorState::updateEditorInput()
{
	//Add a tile
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!this->sidebar.getGlobalBounds().contains(this->mousePosView))
		{
			if (!this->textureSelector->getActive())
			{
				this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->textureRect);
			}
			else
			{
				this->textureRect = this->textureSelector->getTextureRect();
			}
		}
	}
	//Remove a tile
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		if (!this->sidebar.getGlobalBounds().contains(this->mousePosView))
		{
			if (!this->textureSelector->getActive())
				this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
		}
	}
}

void EditorState::updateButtons()
{
	/* Update all the buttons in the state */
	for (auto& i : this->buttons)
	{
		i.second->update(this->mousePosView);
	}
}

void EditorState::updateGui()
{
	this->textureSelector->update(this->mousePosWindow);

	if (!this->textureSelector->getActive())
	{
		this->selectorRect.setTextureRect(this->textureRect);
		this->selectorRect.setPosition(this->mousePosGrid.x * this->stateData->gridSize, this->mousePosGrid.y * this->stateData->gridSize);
	}

	//Update cursorText content and position
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y << std::endl <<
		this->mousePosGrid.x << " " << this->mousePosGrid.y << std::endl <<
		this->textureRect.left << " " << this->textureRect.top;
	this->cursonText.setString(ss.str());
	this->cursonText.setPosition(this->mousePosView.x + 64.f, this->mousePosView.y);
}

void EditorState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonClicked("QUIT"))
		this->endState();

	if (this->pmenu->isButtonClicked("SAVE"))
		this->tileMap->saveToFile("tileMap.txt");

	if (this->pmenu->isButtonClicked("LOAD"))
		this->tileMap->loadFromFile("tileMap.txt");
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
	target.draw(this->sidebar);

	if (!this->textureSelector->getActive())
		target.draw(this->selectorRect);

	this->textureSelector->render(target);

	target.draw(this->cursonText);
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->tileMap->render(*target);

	this->renderButtons(*target);
	this->renderGui(*target);

	if (this->paused) //Pause menu render
	{
		this->pmenu->render(*target);
	}
}