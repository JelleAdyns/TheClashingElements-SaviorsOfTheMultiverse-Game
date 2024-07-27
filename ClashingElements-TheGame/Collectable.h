#ifndef COLLECTABLE_H
#define COLLECTABLE_H


#include "AnimatedSprite.h"
class Collectable final : public AnimatedSprite
{
public:
	explicit Collectable(const Point2Int& BottomCenter, bool randomize = true);
	~Collectable();

	Collectable(const Collectable& other) = delete;
	Collectable(Collectable&& other) noexcept = delete;
	Collectable& operator=(const Collectable& other) = delete;
	Collectable& operator=(Collectable&& other) noexcept = delete;

	virtual void Draw() const override;
	virtual void Update() override;

	CircleInt GetHitBox() const;

private:
	static std::unique_ptr<Texture> m_pTexture;
	static int m_InstanceCounter;
	const static int m_Value;

	CircleInt m_HitBox;

	const static int m_Amplitude;
	const float m_Period;
	float m_Time;
};


#endif // !COLLECTABLE_H
