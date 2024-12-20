#ifndef GRAPHICSSETTIGNS_H
#define GRAPHICSSETTINGS_H

class GraphicsSettings
{
public:
	GraphicsSettings();
	virtual ~GraphicsSettings();

	//Variables
	std::string title;
	sf::VideoMode resolution;
	bool fullscreen;
	bool verticalSync;
	unsigned frameRateLimit;
	sf::ContextSettings constextSettings;
	std::vector<sf::VideoMode> videoModes;

	//Functions
	void saveToFile(const std::string path);
	void loadFromFile(const std::string path);
};

#endif
