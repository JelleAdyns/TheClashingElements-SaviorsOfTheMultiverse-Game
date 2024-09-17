#ifndef PALMTREE_H
#define PALMTREE_H

#include "AnimatedSprite.h"
class PalmTree final: public AnimatedSprite
{
public:
	explicit PalmTree(const Point2Int& bottomCenter) :
		AnimatedSprite{ bottomCenter,_T("PalmTree.png"), SpriteInfo{.nrOfCols{ 3 }, .nrOfFrames{ 3 }, .frameTime{ 1.f / 8 }} }
	{}
	virtual ~PalmTree() = default;

	PalmTree(const PalmTree& other) = delete;
	PalmTree(PalmTree&& other) noexcept = delete;
	PalmTree& operator=(const PalmTree& other) = delete;
	PalmTree& operator=(PalmTree&& other) noexcept = delete;
};


#endif // !PALMTREE_H