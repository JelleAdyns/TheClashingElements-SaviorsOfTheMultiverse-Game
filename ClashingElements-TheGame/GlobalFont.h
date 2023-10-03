#pragma once
#include <SDL_ttf.h> 
class GlobalFont
{
public:

    static GlobalFont& Get()
    {
        static GlobalFont font;
        return font;
    }

    static TTF_Font* GetFont() 
    { 
        static TTF_Font* font = TTF_OpenFont("8BitFont.otf", 16);
        return font;
    }

    GlobalFont(const GlobalFont& other) = delete;
    GlobalFont(GlobalFont&& other) noexcept = delete;
    GlobalFont& operator=(const GlobalFont& other) = delete;
    GlobalFont& operator=(GlobalFont&& other) noexcept = delete;
private:

    GlobalFont() {}

   // static GlobalFont s_Font;
};

