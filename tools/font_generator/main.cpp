#include "font_generator.hpp"
#include "../Paths.hpp"
#include <string>
#include <iostream>


int main(int /*argc*/, char* /*argv*/[])
{
    const std::string generated = createGeneratedDirectory("fonts");
    const std::string freeFonts {"/usr/share/fonts/truetype/freefont/"};

    rwc::FontGenerator generator;

    const char* fonts[]
    {
        "FreeMonoBoldOblique"
        , "FreeMonoBold"
        , "FreeMonoOblique"
        , "FreeMono"
        , "FreeMonoBold"
        , "FreeMonoBold"
        , "FreeSansBoldOblique"
        , "FreeSansOblique"
        , "FreeSans"
        , "FreeSerifBoldItalic"
        , "FreeSerifBold"
        , "FreeSerifItalic"
        , "FreeSerif"
    };

    for (auto& font : fonts)
    {
        const std::string fontPath = freeFonts + font + ".ttf";
        const std::string metadataPath = generated + font + ".meta";
        const std::string atlasPath = generated + font + ".png";;
        generator.generate(fontPath.c_str(), atlasPath.c_str(), metadataPath.c_str());
    }
    return 0;
}
