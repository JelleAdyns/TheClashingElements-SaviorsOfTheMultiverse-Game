#ifndef GLOBALFONT_H
#define GLOBALFONT_H

#include "Engine.h"

class GlobalFont
{
public:

    static GlobalFont& Get()
    {
        static GlobalFont font;
        return font;
    }

    const Font& GetFont() 
    { 
        return m_Font;
    }

    GlobalFont(const GlobalFont& other) = delete;
    GlobalFont(GlobalFont&& other) noexcept = delete;
    GlobalFont& operator=(const GlobalFont& other) = delete;
    GlobalFont& operator=(GlobalFont&& other) noexcept = delete;
private:

    GlobalFont() {}
    Font m_Font{ L"ClashingFont.ttf", 16, false, false, true };
   // static GlobalFont s_Font;
};

#endif // !GLOBALFONT_H

