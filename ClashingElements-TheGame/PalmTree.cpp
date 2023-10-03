#include "pch.h"
#include "PalmTree.h"

const Texture* PalmTree::m_pTexture{ nullptr };
int PalmTree::m_InstanceCounter{ 0 };


PalmTree::PalmTree(const Point2f& bottomCenter):
	AnimatedSprite{bottomCenter, 3, 3, 1.f/8 }
{
	++m_InstanceCounter;

	if (m_pTexture == nullptr)
	{
		m_pTexture = new Texture{ "PalmTree.png" };
	}
	AnimatedSprite::SetTexture(m_pTexture);
}

PalmTree::~PalmTree()
{
	--m_InstanceCounter;
	if (m_InstanceCounter == 0)
	{
		delete m_pTexture;
		m_pTexture = nullptr;
	}
}