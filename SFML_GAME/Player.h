#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player :
    public Entity
{
private:
    //Variables
    bool attacking;

    //Initializer functions
    void initializeVariables();
    void initiazlizeComponents();
public:
    Player(float x, float y, std::map<std::string, sf::Texture>& texture_sheets);
    virtual ~Player();

    //Functions
    void updateAttack();
    void updateAnimation(const float& dt);
    virtual void update(const float& dt);
};

#endif
