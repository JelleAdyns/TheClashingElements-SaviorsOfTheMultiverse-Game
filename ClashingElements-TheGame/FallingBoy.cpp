#include "FallingBoy.h"

const int FallingBoy::m_FallingSpeed{ 30 };
const int FallingBoy::m_NrOfBoys{ 10 };


FallingBoy::FallingBoy(const Point2Int& bottomCenter) :
	AnimatedSprite{ Point2Int{},_T("FallingBoys.png"), SpriteInfo{.nrOfCols{ 3 }, .nrOfFrames{ 30 }, .frameTime{ 1.f / 8}}, false }
{
	int distanceFromBorder{ 40 };
	const auto& window = ENGINE.GetWindowRect();
	for (int i = 0; i < m_SpriteInfo.nrOfRows/2; i++)
	{
		m_VecPositions.push_back(Point2Int{ distanceFromBorder ,
									   -(DestRect().height + (window.height / (m_SpriteInfo.nrOfRows / 2 - 1)) * i) });
	}
	for (int i = 0; i < m_SpriteInfo.nrOfRows/2; i++)
	{
		m_VecPositions.push_back(Point2Int{ window.width - distanceFromBorder,
									   -(DestRect().height + (window.height / (m_SpriteInfo.nrOfRows / 2 - 1)) * i) });
	}
}

void FallingBoy::Draw() const
{
	for (int i = 0; i < m_VecPositions.size(); ++i)
	{

		ENGINE.PushTransform();
		ENGINE.Translate(static_cast<int>(std::round(m_VecPositions[i].x)) , static_cast<int>(std::round(m_VecPositions[i].y)) + DestRect().height /2);
		ENGINE.Rotate(float(i%2 == 0 ? 30 : -30), m_BottomCenter.x, m_BottomCenter.y+ DestRect().height / 2);
		ENGINE.DrawTexture(GetTexture(), DestRect(), RectInt{DestRect().width * m_CurrentCol,
											   DestRect().height * (i),
											   DestRect().width,
											   DestRect().height});
		ENGINE.PopTransform();
	}
}

void FallingBoy::UpdatePos()
{
	AnimatedSprite::Update();
	for (int i = 0; i < m_SpriteInfo.nrOfRows; i++)
	{
		m_VecPositions[i].y += m_FallingSpeed * ENGINE.GetDeltaTime();
		if (m_VecPositions[i].y > ENGINE.GetWindowRect().height) 
			m_VecPositions[i].y -= (ENGINE.GetWindowRect().height + (ENGINE.GetWindowRect().height / (m_SpriteInfo.nrOfRows / 2 - 1.f)));
	}
}