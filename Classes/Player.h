#pragma once

#include <cstdint>

#include "../Headers/Vector2D.h"

class Player
{
public:
	Player() = default;
	Player(int lives, Vector2D position);
	void UpdateDirection(Vector2D direction);
	void UpdatePosition(float deltaTime);
	int GetPosX();
	int GetPosY();

private:
	int lives;
	Vector2D pos;
	Vector2D dir;
};