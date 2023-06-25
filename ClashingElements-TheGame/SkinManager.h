#pragma once

#include <vector>

class Texture;

class SkinManager final
{
public:
	explicit SkinManager();
	~SkinManager();

	SkinManager(const SkinManager& other) = delete;
	SkinManager(SkinManager&& other) noexcept = delete;
	SkinManager& operator=(const SkinManager& other) = delete;
	SkinManager& operator=(SkinManager&& other) noexcept = delete;

private:
	std::vector<Texture*> m_pSkins;
};

