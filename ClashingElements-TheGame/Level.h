#pragma once
class Level final
{
public:
	explicit Level();
	~Level();

	Level(const Level& other) = delete;
	Level(Level&& other) noexcept = delete;
	Level& operator=(const Level& other) = delete;
	Level& operator=(Level&& other) noexcept = delete;
};

