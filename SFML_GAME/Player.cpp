#include "stdafx.h"
#include "Player.h"

//Initializer functions
void Player::initializeVariables()
{
	this->attacking = false;
}

void Player::initiazlizeComponents()
{

}


//Constructors/Destructors
Player::Player(float x, float y, std::map<std::string, sf::Texture>& texture_sheets)
{
	this->initializeVariables();
	this->initiazlizeComponents();

	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite, 110.f, 70.f, 32.f, 56.f);
	this->createMovementComponent(400.f, 12.f, 6.f);
	this->createAnimationComponent(texture_sheets);

	this->animationComponent->addAnimation("IDLE", "PLAYER_IDLE_SHEET", 2.5f, 0, 0, 0, 0, 256, 256);
	this->animationComponent->addAnimation("WALK", "PLAYER_WALK_SHEET", 1.f, 0, 0, 7, 4, 256, 256);
	this->animationComponent->addAnimation("ATTACK", "PLAYER_ATTACK_SHEET", 10.f, 0, 0, 7, 0, 256, 256);
}

Player::~Player()
{

}


//Functions
void Player::updateAttack()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->attacking = true;
	}
}

void Player::updateAnimation(const float& dt)
{
	if (this->attacking)
	{
		//Przyda siê gdy sheet od ataku bêdzie szerszy ni¿ pozosta³e :)
		////set origin depending on direction
		//if (this->sprite.getScale().x > 0.f) //Left
		//{
		//	this->sprite.setOrigin(0.f, 0.f);
		//}
		//else //Right
		//{
		//	this->sprite.setOrigin(252.f, 0.f);
		//}

		//Animate and check for animaiton end
		if (this->animationComponent->play("ATTACK", dt, true))
		{
			this->attacking = false;

			//Now it is totally useless
			//if (this->sprite.getScale().x > 0.f) //Left
			//{
			//	this->sprite.setOrigin(0.f, 0.f);
			//}
			//else //Right
			//{
			//	this->sprite.setOrigin(252.f, 0.f);
			//}
		}
	}

	if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("IDLE", dt);
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		if (this->sprite.getScale().x < 0.f)
		{
			this->sprite.setOrigin(0.f, 0.f);
			this->sprite.setScale(1.f, 1.f);
		}

		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		if (this->sprite.getScale().x > 0.f)
		{
			this->sprite.setOrigin(252.f, 0.f);
			this->sprite.setScale(-1.f, 1.f);
		}

		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
}

void Player::update(const float& dt)
{
	Entity::update(dt);

	this->updateAttack();
	
	this->updateAnimation(dt);

	this->hitboxComponent->update();
}

