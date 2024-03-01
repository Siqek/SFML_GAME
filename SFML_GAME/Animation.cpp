#include "stdafx.h"
#include "Animation.h"

Animation::Animation(sf::Sprite& sprite, sf::Texture& texture_sheet, float animation_timer, int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
	: sprite(sprite), textureSheet(texture_sheet),
	animationTimer(animation_timer), timer(animation_timer), done(false),
	width(width), height(height)
{
	this->startRect = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
	this->currentRect = this->startRect;
	this->endRect = sf::IntRect(frames_x * width, frames_y * height, width, height);

	this->sprite.setTexture(this->textureSheet, true);
	this->sprite.setTextureRect(this->startRect);
}


//Accessors
const bool& Animation::isDone() const
{
	return this->done;
}

const bool& Animation::play(const float& dt)
{
	this->done = false;

	//Update timer
	this->timer += 100.f * dt;

	if (this->timer >= this->animationTimer)
	{
		//reset timer
		this->timer = 0.f;

		//Animate
		if (this->currentRect.left != this->endRect.left)
		{
			this->currentRect.left += this->width;
		}
		else //Reset
		{
			this->currentRect.left = this->startRect.left;
			if (this->currentRect.top != this->endRect.top)
				this->currentRect.top += this->height;
			else
			{
				this->currentRect.top = this->startRect.top;
				this->done = true;
			}
		}

		this->sprite.setTextureRect(this->currentRect);
	}

	return this->done;
}

const bool& Animation::play(const float& dt, float mod_percent)
{
	this->done = false;

	//Check the minimum modifier value
	if (mod_percent < 0.5f)
		mod_percent = 0.5f;

	//Update timer
	this->timer += mod_percent * 100.f * dt;

	if (this->timer >= this->animationTimer)
	{
		//reset timer
		this->timer = 0.f;

		//Animate
		if (this->currentRect.left != this->endRect.left)
		{
			this->currentRect.left += this->width;
		}
		else //Reset
		{
			this->currentRect.left = this->startRect.left;
			if (this->currentRect.top != this->endRect.top)
				this->currentRect.top += this->height;
			else
			{
				this->currentRect.top = this->startRect.top;
				this->done = true;
			}
		}

		this->sprite.setTextureRect(this->currentRect);
	}

	return this->done;
}

void Animation::reset()
{
	this->timer = this->animationTimer;
	this->currentRect = this->startRect;
}

void Animation::updateTexture()
{
	this->sprite.setTexture(this->textureSheet);
}
