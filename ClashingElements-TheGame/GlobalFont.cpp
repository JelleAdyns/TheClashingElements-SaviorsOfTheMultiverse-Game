#include "GlobalFont.h"

namespace globalFont
{
	std::unique_ptr<Font> clashingFont{nullptr};

	void InitFont()
	{
		clashingFont = std::make_unique<Font>(L"ClashingFont.ttf", 12, false, false, true);
	}
	Font& GetFont()
	{
		return *clashingFont;
	}
}
