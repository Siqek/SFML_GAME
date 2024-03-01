#ifndef KEYBOARDEVENTS_H
#define KEYBOARDEVENTS_H

enum keys_status
{
	KEY_IDLE = 0,
	KEY_PRESSED,
	KEY_WASPRESSED
};

class KeyboardEvents
{
private:
	//Variables
	std::map<std::string, int>* keys;
	std::map<std::string, int> keysStatus;

public:
	KeyboardEvents(std::map<std::string, int>* keys);

	//Accessors
	const bool isPressed(std::string key) const;
	const bool isWaspressed(std::string key) const;

	//Functions
	void updateKeysStatus();
};

#endif
