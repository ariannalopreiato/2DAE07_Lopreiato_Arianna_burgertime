#include "MrEgg.h"
#include "Texture2D.h"

MrEgg::MrEgg(Rectf enemy)
	:Enemy(EnemyType::MrEgg, enemy)
	//, m_pTexture{ new Texture2D()}

{
	m_Points = 300;
	//m_pTexture = new Texture2D{};
}