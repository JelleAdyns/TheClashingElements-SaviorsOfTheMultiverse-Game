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

    static const Font& GetFont() 
    { 
        static std::unique_ptr<Font> font = std::make_unique<Font>(L"8BitFont.otf", 16, false, false, true);
        return *font;
    }

    GlobalFont(const GlobalFont& other) = delete;
    GlobalFont(GlobalFont&& other) noexcept = delete;
    GlobalFont& operator=(const GlobalFont& other) = delete;
    GlobalFont& operator=(GlobalFont&& other) noexcept = delete;
private:

    GlobalFont() {}

   // static GlobalFont s_Font;
};

#endif // !GLOBALFONT_H

