#include "GameFont.h"

namespace gameFont
{
	Font& GetFont()
	{
		return ResourceManager::GetInstance().GetFont(_T("ClashingFont.ttf"), true);
	}
}
