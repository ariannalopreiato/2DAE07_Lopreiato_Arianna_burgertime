#include "MiniginPCH.h"
#include "Player.h"
#include "InputManager.h"
#include "Command.h"

dae::Player::Player()
{
	//m_MoveUp = new MoveCommand(*this, 0.0f, 1.0f);
	//InputManager::GetInstance().SetCommandController(m_MoveUp, ControllerButton::ButtonY);
}

dae::Player::~Player()
{}

void dae::Player::Update(float)
{
	//Command* command = InputManager::GetInstance().HandleInput(m_PlayerNr); //check every frame if any button is pressed
	//if (command)
	//	command->Execute();
}

void dae::Player::Move(float velocityX, float velocityY)
{
	//todo: fix moving
	m_HitBox.bottom += velocityY * m_Speed;
	m_HitBox.left += velocityX * m_Speed;
}
