#include "GlobalFont.h"

namespace globalFont
{
	Font& GetFont()
	{
		return ResourceManager::GetInstance().GetFont(_T("ClashingFont.ttf"), true);
	}
}
