#include "stdafx.h"
#include "KeyboardEvents.h"

KeyboardEvents::KeyboardEvents(std::map<std::string, int>* keys)
{
	this->keys = keys;
}


//Accessors
const bool KeyboardEvents::isKeyPressed(std::string key) const
{
	return (this->keysStatus.at(key) == KEY_PRESSED || this->isKeyUp(key) || this->isKeyDown(key));
}

const bool KeyboardEvents::isKeyUp(std::string key) const
{
	return (this->keysStatus.at(key) == KEY_UP);
}

const bool KeyboardEvents::isKeyDown(std::string key) const
{
	return (this->keysStatus.at(key) == KEY_DOWN);
}

//Functions
void KeyboardEvents::updateKeysStatus()
{
	for (auto it = this->keys->begin(); it != this->keys->end(); ++it)
	{
		if (this->keysStatus[it->first] == KEY_PRESSED || this->keysStatus[it->first] == KEY_DOWN)
			this->keysStatus[it->first] = KEY_UP;
		else
			this->keysStatus[it->first] = KEY_IDLE;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(it->second)))
		{
			if (this->keysStatus[it->first] == KEY_IDLE)
				this->keysStatus[it->first] = KEY_DOWN;
			else
				this->keysStatus[it->first] = KEY_PRESSED;
		}
	}
}
