#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include "Animation.h"

class AnimationComponent
{
private:
	//Variables
	sf::Sprite& sprite;
	std::map<std::string, sf::Texture>& textureSheets;
	std::map<std::string, Animation*> animations;
	Animation* lastAnimation;
	Animation* priorityAnimation;

public:
	AnimationComponent(sf::Sprite& sprite, std::map<std::string, sf::Texture>& texture_sheets);
	virtual ~AnimationComponent();

	//Accessors
	const bool& isDone(const std::string key);

	//Functions
	void addAnimation(const std::string animation_key, const std::string texture_key,
		float animation_timer,
		int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height);

	const bool& play(const std::string key, const float& dt, const bool priority = false);
	const bool& play(const std::string key, const float& dt, const float& modifier, const float& modifier_max, const bool priority = false);
};

#endif
