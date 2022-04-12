#pragma once

namespace dae
{
	struct Vector2f
	{
		float x, y;
	};

	struct Rect
	{
		float left, bottom, width, height;
	};

	class Command;
	class Player
	{
	public:
		Player();
		~Player();
		void Update(float elapsedTime);
		void Move(float velocityX, float velocityY);
	private:
		float m_Speed{ 0.0f };
		Vector2f m_Velocity{ 0.0f, 0.0f };
		int m_PlayerNr{ 0 };
		Rect m_HitBox{ 0.0f, 0.0f, 0.0f, 0.0f };
		//MoveCommand* m_MoveUp;
		//MoveCommand* m_MoveDown;
		//MoveCommand* m_MoveLeft;
		//MoveCommand* m_MoveRight;
	};
}
