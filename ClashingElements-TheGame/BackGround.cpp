#include "pch.h"
#include "BackGround.h"


BackGround::BackGround(const Point2f& center, const std::string& filePath) :
	AnimatedSprite{ center, 3, 3, 1.f / 8 }
{
	m_pTexture = new Texture{filePath} ;
	AnimatedSprite::SetTexture(m_pTexture);
}
BackGround::~BackGround()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}
void BackGround::randomFun()
{

}