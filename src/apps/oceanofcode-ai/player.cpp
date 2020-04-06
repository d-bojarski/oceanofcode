#include "player.h"

//---------------------------------------
//------- Constructors/Destructors ------
//---------------------------------------
Player::Player() :
	id(-1),
	x(-1),
	y(-1),
	life(6),
	torpedoCooldown(-1),
	sonarCooldown(-1),
	silenceCooldown(-1),
	mineCooldown(-1)
{
}

Player::~Player()
{
}

//---------------------------------------
//---- Public methods implementation ----
//---------------------------------------
