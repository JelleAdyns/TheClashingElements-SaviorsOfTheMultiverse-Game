#ifndef MOBILITYITEM_H
#define MOBILITYITEM_H


#include "Player.h"
#include "Enemy.h"

class MobilityItem
{
public:
	explicit MobilityItem() = default;
	virtual ~MobilityItem() = default;

	MobilityItem(const MobilityItem& other) = delete;
	MobilityItem(MobilityItem&& other) noexcept = delete;
	MobilityItem& operator=(const MobilityItem& other) = delete;
	MobilityItem& operator=(MobilityItem&& other) noexcept = delete;

};

class MobilityInteract
{
public:

	void operator()(const Character* pCharacter)
	{

	}
};


#endif // !MOBILITYITEM_H
