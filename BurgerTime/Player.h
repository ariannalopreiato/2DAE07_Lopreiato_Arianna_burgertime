#pragma once
struct Vector2f
{
	float x, y;
};

struct Rect
{
	float left, bottom, width, height;
};

class Player
{
public:
	Player(int playerIdx);
	void Update(float elapsedTime);
	void Move(float velocityX, float velocityY);
	int GetPlayerIdx();
	void RemoveLife();
	void KillCharacter();
	void ThrowPepper();

private:
	float m_Speed{ 0.0f };
	Vector2f m_Velocity{ 0.0f, 0.0f };
	int m_PlayerNr{ 0 };
	Rect m_HitBox{ 0.0f, 0.0f, 0.0f, 0.0f };
	int m_PlayerIdx{ 0 };
	int m_Lives{ 3 };
	int m_PepperShots{ 5 };
	int m_CurrentPepperShots{ m_PepperShots };
	int m_CurrentLives{ m_Lives };
};