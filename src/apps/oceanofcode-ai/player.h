#pragma once

class Player
{
public:
	Player();
	Player(
		int id,
		int life,
		int torpedoCooldown,
		int sonarCooldown,
		int silenceCooldown,
		int mineCooldown);
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

