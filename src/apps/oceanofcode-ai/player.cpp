#include "player.h"

//---------------------------------------
//------- Constructors/Destructors ------
//---------------------------------------
Player::Player() : 
	Player(-1, -1, -1, -1, -1, -1)
{
}

Player::Player(int id, int life, int torpedoCooldown, int sonarCooldown, int silenceCooldown, int mineCooldown) :
	id(id),
	x(-1),
	y(-1),
	life(life),
	torpedoCooldown(torpedoCooldown),
	sonarCooldown(sonarCooldown),
	silenceCooldown(silenceCooldown),
	mineCooldown(mineCooldown)
{
}

Player::~Player()
{
}

//---------------------------------------
//---- Public methods implementation ----
//---------------------------------------
