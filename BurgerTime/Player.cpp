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

void Player::RemoveLife()
{
	if (m_Lives > 1)
		--m_Lives;
	else
		KillCharacter();
}

void Player::KillCharacter()
{
}

void Player::ThrowPepper()
{
	if (m_CurrentPepperShots > 4)
	{
		--m_CurrentPepperShots;
		//throw pepper
	}
}
