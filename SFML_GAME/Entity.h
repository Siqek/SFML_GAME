#ifndef ENTITY_H
#define ENTITY_H

#include "HitboxComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"

class Entity
{
private:
	//Functions
	void initializeVariables();

protected:
	sf::Sprite sprite;

	HitboxComponent* hitboxComponent;
	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;

public:
	Entity();
	virtual ~Entity();

	//Component funtions
	void setTexture(sf::Texture& texture);
	void createHitboxComponent(sf::Sprite& sprite,
		float offset_x, float offset_y,
		float width, float height);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void createAnimationComponent(std::map<std::string, sf::Texture>& texture_sheets);

	//Functions
	virtual void setPosition(const float x, const float y);
	virtual void move(const float dir_x, const float dir_y, const float& dt);

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget& target);
};

#endif
