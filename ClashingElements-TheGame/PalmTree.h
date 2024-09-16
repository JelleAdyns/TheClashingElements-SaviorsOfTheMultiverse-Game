#ifndef PALMTREE_H
#define PALMTREE_H

#include "AnimatedSprite.h"
class PalmTree final: public AnimatedSprite
{
public:
	explicit PalmTree(const Point2Int& bottomCenter);
	virtual ~PalmTree();

	PalmTree(const PalmTree& other) = delete;
	PalmTree(PalmTree&& other) noexcept = delete;
	PalmTree& operator=(const PalmTree& other) = delete;
	PalmTree& operator=(PalmTree&& other) noexcept = delete;

private:

	static std::unique_ptr<Texture> m_pTexture;
	static int m_InstanceCounter;
};


#endif // !PALMTREE_H