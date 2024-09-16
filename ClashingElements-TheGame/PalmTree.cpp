#include "PalmTree.h"

std::unique_ptr<Texture> PalmTree::m_pTexture{ nullptr };
int PalmTree::m_InstanceCounter{ 0 };


PalmTree::PalmTree(const Point2Int& bottomCenter):
	AnimatedSprite{bottomCenter, 3, 3, 1.f/8 }
{
	++m_InstanceCounter;

	if (m_pTexture == nullptr)
	{
		m_pTexture = std::make_unique<Texture>(_T("PalmTree.png"));
	}
	AnimatedSprite::SetTexture(m_pTexture.get());
}

PalmTree::~PalmTree()
{
	--m_InstanceCounter;
	if (m_InstanceCounter == 0)
	{
		m_pTexture = nullptr;
	}
}