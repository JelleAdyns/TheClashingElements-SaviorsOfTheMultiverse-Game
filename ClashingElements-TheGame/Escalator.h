#pragma once
#include"Tile.h"
#include"MobilityItem.h"

class Escalator final : public MobilityItem
{
public:
	explicit Escalator(const Point2f& startCenter, const Point2f& endCenter, bool isDownwards);
	~Escalator() = default;

	Escalator(const Escalator& other) = delete;
	Escalator(Escalator&& other) noexcept = delete;
	Escalator& operator=(const Escalator& other) = delete;
	Escalator& operator=(Escalator&& other) noexcept = delete;

	int GetVelocity(const Point2f& bottomCenter) const;

private:
	const static int m_Speed;

	const int m_Velocity;
	const Rectf m_Area;
	const Rectf m_TargetRect;
};

