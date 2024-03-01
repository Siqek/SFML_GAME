#include "stdafx.h"
#include "KeyboardEvents.h"

KeyboardEvents::KeyboardEvents(std::map<std::string, int>* keys)
{
	this->keys = keys;
}


//Accessors
const bool KeyboardEvents::isPressed(std::string key) const
{
	if (this->keysStatus.at(key) == KEY_PRESSED)
		return true;
	
	return false;
}

const bool KeyboardEvents::isWaspressed(std::string key) const
{
	if (this->keysStatus.at(key) == KEY_WASPRESSED)
		return true;

	return false;
}

//Functions
void KeyboardEvents::updateKeysStatus()
{
	for (auto it = this->keys->begin(); it != this->keys->end(); ++it)
	{
		if (this->keysStatus[it->first] == KEY_PRESSED)
			this->keysStatus[it->first] = KEY_WASPRESSED;
		else
			this->keysStatus[it->first] = KEY_IDLE;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(it->second)))
		{
			this->keysStatus[it->first] = KEY_PRESSED;
		}
	}
}
