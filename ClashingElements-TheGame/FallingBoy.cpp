#include "pch.h"
#include "FallingBoy.h"

const Texture* FallingBoy::m_pTexture{ nullptr };
int FallingBoy::m_InstanceCounter{ 0 };
const int FallingBoy::m_FallingSpeed{ 30 };
const int FallingBoy::m_NrOfBoys{ 10 };


FallingBoy::FallingBoy(const Point2f& bottomCenter, const Rectf& window) :
	AnimatedSprite{ Point2f{}, 3, 30, 1.f / 8, false },
	m_Window{window}

{
	++m_InstanceCounter;

	if (m_pTexture == nullptr)
	{
		m_pTexture = new Texture{ "FallingBoys.png" };
	}
	AnimatedSprite::SetTexture(m_pTexture);

	float distanceFromBorder{ 50.f };
	for (int i = 0; i < m_NrOfRows/2; i++)
	{
		m_VecPositions.push_back(Point2f{ distanceFromBorder ,
									   -(SrcRect().height + (window.height / (m_NrOfRows / 2 - 1)) * i) });
	}
	for (int i = 0; i < m_NrOfRows/2; i++)
	{
		m_VecPositions.push_back(Point2f{ window.width - distanceFromBorder,
									   -(SrcRect().height + (window.height / (m_NrOfRows / 2 - 1)) * i) });
	}
}

FallingBoy::~FallingBoy()
{
	--m_InstanceCounter;
	if (m_InstanceCounter == 0)
	{
		delete m_pTexture;
		m_pTexture = nullptr;
	}
}
void FallingBoy::Draw() const
{
	for (int i = 0; i < m_VecPositions.size(); ++i)
	{
		glPushMatrix();
		glTranslatef(m_VecPositions[i].x , m_VecPositions[i].y + SrcRect().height /2, 0);
		glRotatef(float(i%2 == 0 ? 30 : -30), 0, 0, 1);
		glTranslatef(-SrcRect().width / 2,  - SrcRect().height / 2, 0);
		m_pTexture->Draw(m_BottomCenter, Rectf{SrcRect().width * m_CurrentCol,
											   SrcRect().height * (i+1),
											   SrcRect().width,
											   SrcRect().height});
		glPopMatrix();
	}
}

void FallingBoy::UpdatePos(float elapsedSec)
{
	for (int i = 0; i < m_NrOfRows; i++)
	{
		m_VecPositions[i].y += m_FallingSpeed * elapsedSec;
		if (m_VecPositions[i].y > m_Window.height) m_VecPositions[i].y = -(m_Window.height / (m_NrOfRows / 2 - 1));
	}
}

void FallingBoy::Reset(float yDist)
{
	m_BottomCenter.y = -yDist;
}