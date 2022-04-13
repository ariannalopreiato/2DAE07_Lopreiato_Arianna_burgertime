#include "Player.h"

Player::Player(int playerIdx)
	: m_PlayerIdx(playerIdx)
{}

void Player::Update(float)
{
}

void Player::Move(float velocityX, float velocityY)
{
	//todo: fix moving
	m_HitBox.bottom += velocityY * m_Speed;
	m_HitBox.left += velocityX * m_Speed;
}

int Player::GetPlayerIdx()
{
	return m_PlayerIdx;
}
