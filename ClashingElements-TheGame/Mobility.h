#pragma once
class Mobility
{
public:
	explicit Mobility();
	~Mobility() = default;

	Mobility(const Mobility& other) = delete;
	Mobility(Mobility&& other) noexcept = delete;
	Mobility& operator=(const Mobility& other) = delete;
	Mobility& operator=(Mobility&& other) noexcept = delete;

	virtual void Interact() const = 0;

};

