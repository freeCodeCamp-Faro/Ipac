#include <cstdint>
#include <iostream>
#include "../Headers/Vector2D.h"
#include "Player.h"
#include "../Headers/Constants.h"

Player::Player(int lifeCount, Vector2D position)
{
	this->lives = lifeCount;
	this->pos.x = position.x;
	this->pos.y = position.y;
	this->dir.x = 0;
	this->dir.y = 0;
}

//Player::Player()
//{}

void Player::UpdatePosition(float deltaTime)
{
	this->pos.x += this->dir.x * deltaTime * PLAYER_SPEED;
	this->pos.y += this->dir.y * deltaTime * PLAYER_SPEED;
}

void Player::UpdateDirection(Vector2D direction)
{
	if(direction.x != 0)
	{
		this->dir.x = direction.x;
		this->dir.y = 0;
	}

	if(direction.y != 0)
	{
		this->dir.y = direction.y;
		this->dir.x = 0;
	}
}

int Player::GetPosX()
{
	return this->pos.x;
}

int Player::GetPosY()
{
	return this->pos.y;
}