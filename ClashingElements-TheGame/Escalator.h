#ifndef ESCALATOR_H
#define ESCALATOR_H


#include"Tile.h"
#include"MobilityItem.h"

class Escalator final : public MobilityItem
{
public:
	explicit Escalator(const Point2Int& startCenter, const Point2Int& endCenter, bool isDownwards);
	virtual ~Escalator() = default;

	Escalator(const Escalator& other) = delete;
	Escalator(Escalator&& other) noexcept = delete;
	Escalator& operator=(const Escalator& other) = delete;
	Escalator& operator=(Escalator&& other) noexcept = delete;

	int GetVelocity(const Point2Int& bottomCenter) const;

private:
	const static int m_Speed;

	const int m_Velocity;
	const RectInt m_Area;
	const RectInt m_TargetRect;
};


#endif // !ESCALATOR_H
