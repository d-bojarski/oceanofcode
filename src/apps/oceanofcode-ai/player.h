#pragma once

class Player
{
public:
	Player();
	~Player();


public:
	int id;

	int x;
	int y;

	int life;
	int torpedoCooldown;
	int sonarCooldown;
	int silenceCooldown;
	int mineCooldown;

};

