#pragma once
#include <string>
class FontPath
{
public:
    static FontPath& Get()
    {
        static FontPath fontPath {};
        return fontPath;
    }

    const std::string& GetPath() { return m_Path;}

    FontPath(const FontPath& other) = delete;
    FontPath(FontPath&& other) noexcept = delete;
    FontPath& operator=(const FontPath& other) = delete;
    FontPath& operator=(FontPath&& other) noexcept = delete;
private:

    FontPath() {}

    const std::string m_Path{"8BitFont.otf"};
};
