#include "FallingBoy.h"

std::unique_ptr<Texture> FallingBoy::m_pTexture{ nullptr };
int FallingBoy::m_InstanceCounter{ 0 };
const int FallingBoy::m_FallingSpeed{ 30 };
const int FallingBoy::m_NrOfBoys{ 10 };


FallingBoy::FallingBoy(const Point2Int& bottomCenter, const RectInt& window) :
	AnimatedSprite{ Point2Int{}, 3, 30, 1.f / 8, false },
	m_Window{window}

{
	++m_InstanceCounter;

	if (m_pTexture == nullptr)
	{
		m_pTexture = std::make_unique<Texture>(L"FallingBoys.png");
	}
	AnimatedSprite::SetTexture(m_pTexture.get());

	int distanceFromBorder{ 50 };
	for (int i = 0; i < m_NrOfRows/2; i++)
	{
		m_VecPositions.push_back(Point2Int{ distanceFromBorder ,
									   -(DestRect().height + (window.height / (m_NrOfRows / 2 - 1)) * i) });
	}
	for (int i = 0; i < m_NrOfRows/2; i++)
	{
		m_VecPositions.push_back(Point2Int{ window.width - distanceFromBorder,
									   -(DestRect().height + (window.height / (m_NrOfRows / 2 - 1)) * i) });
	}
}

FallingBoy::~FallingBoy()
{
	--m_InstanceCounter;
	if (m_InstanceCounter == 0)
	{
		m_pTexture = nullptr;
	}
}
void FallingBoy::Draw() const
{
	for (int i = 0; i < m_VecPositions.size(); ++i)
	{

		ENGINE.PushTransform();
		ENGINE.Translate(m_VecPositions[i].x , m_VecPositions[i].y + DestRect().height /2);
		ENGINE.Rotate(float(i%2 == 0 ? 30 : -30), m_BottomCenter.x, m_BottomCenter.y+ DestRect().height / 2);
		//ENGINE.Translate(-DestRect().width / 2,  - DestRect().height / 2);
		ENGINE.DrawTexture(*m_pTexture, m_BottomCenter, RectInt{DestRect().width * m_CurrentCol,
											   DestRect().height * (i),
											   DestRect().width,
											   DestRect().height});
		ENGINE.PopTransform();
	}
}

void FallingBoy::UpdatePos()
{
	AnimatedSprite::Update();
	for (int i = 0; i < m_NrOfRows; i++)
	{
		float posY{ static_cast<float>(m_VecPositions[i].y) };
		posY += m_FallingSpeed * ENGINE.GetDeltaTime();
		m_VecPositions[i].y = static_cast<int>(std::round(posY));
		if (m_VecPositions[i].y > m_Window.height) m_VecPositions[i].y = -(m_Window.height / (m_NrOfRows / 2 - 1));
	}
}

//void FallingBoy::Reset(float yDist)
//{
//	m_BottomCenter.y = -yDist;
//}