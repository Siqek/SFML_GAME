#include "stdafx.h"
#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, std::map<std::string, sf::Texture>& texture_sheets)
	: sprite(sprite), textureSheets(texture_sheets), lastAnimation(nullptr), priorityAnimation(nullptr)
{

}

AnimationComponent::~AnimationComponent()
{
	for (auto& i : this->animations)
	{
		delete i.second;
	}
}


//Accessors
const bool& AnimationComponent::isDone(const std::string key)
{
	return this->animations[key]->isDone();
}

//Functions
void AnimationComponent::addAnimation(const std::string animation_key, const std::string texture_key,
	float animation_timer,
	int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
{
	this->animations[animation_key] = new Animation(
		this->sprite, this->textureSheets[texture_key],
		animation_timer,
		start_frame_x, start_frame_y, frames_x, frames_y, width, height
	);
}

const bool& AnimationComponent::play(const std::string key, const float& dt, const bool priority)
{
	if (this->priorityAnimation)
	{
		if (this->priorityAnimation == this->animations[key])
		{
			if (this->lastAnimation != this->animations[key])
			{
				if (this->lastAnimation != nullptr)
					this->lastAnimation->reset();

				this->lastAnimation = this->animations[key];
				this->animations[key]->updateTexture();
			}

			if (this->animations[key]->play(dt))
			{
				this->priorityAnimation = nullptr;
			}
		}
	}
	else
	{
		if (priority)
		{
			this->priorityAnimation = this->animations[key];
		}

		if (this->lastAnimation != this->animations[key])
		{
			if (this->lastAnimation != nullptr)
				this->lastAnimation->reset();

			this->lastAnimation = this->animations[key];
			this->animations[key]->updateTexture();
		}

		this->animations[key]->play(dt);
	}

	return this->animations[key]->isDone();
}

const bool& AnimationComponent::play(const std::string key, const float& dt, const float& modifier, const float& modifier_max, const bool priority)
{
	if (this->priorityAnimation)
	{
		if (this->priorityAnimation == this->animations[key])
		{
			if (this->lastAnimation != this->animations[key])
			{
				if (this->lastAnimation != nullptr)
					this->lastAnimation->reset();

				this->lastAnimation = this->animations[key];
				this->animations[key]->updateTexture();
			}

			if (this->animations[key]->play(dt, abs(modifier / modifier_max)))
			{
				this->priorityAnimation = nullptr;
			}
		}
	}
	else
	{
		if (priority)
		{
			this->priorityAnimation = this->animations[key];
		}

		if (this->lastAnimation != this->animations[key])
		{
			if (this->lastAnimation != nullptr)
				this->lastAnimation->reset();

			this->lastAnimation = this->animations[key];
			this->animations[key]->updateTexture();
		}

		this->animations[key]->play(dt, abs(modifier / modifier_max));
	}

	return this->animations[key]->isDone();
}