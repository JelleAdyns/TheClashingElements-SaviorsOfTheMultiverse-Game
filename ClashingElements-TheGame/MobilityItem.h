#pragma once
#include "Player.h"
#include "Enemy.h"
#include <utils.h>
class MobilityItem
{
public:
	explicit MobilityItem() = default;
	~MobilityItem() = default;

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

