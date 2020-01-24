#include "font_generator.hpp"
#include "../Paths.hpp"
#include <string>
#include <iostream>


int main(int /*argc*/, char* /*argv*/[])
{
    const std::string generated = createGeneratedDirectory("fonts");
//    const std::string fonts_path {"/usr/share/fonts/truetype/freefont/"};
//    const char* fonts[]
//            {
//                    "FreeMonoBoldOblique"
//                    , "FreeMonoBold"
//                    , "FreeMonoOblique"
//                    , "FreeMono"
//                    , "FreeMonoBold"
//                    , "FreeMonoBold"
//                    , "FreeSansBoldOblique"
//                    , "FreeSansOblique"
//                    , "FreeSans"
//                    , "FreeSerifBoldItalic"
//                    , "FreeSerifBold"
//                    , "FreeSerifItalic"
//                    , "FreeSerif"
//            };


    const std::string fonts_path {"../../../app/assets/fonts/"};
    const char* fonts[]
            {
                    "SagarNormal"
            };
    rwc::FontGenerator generator;

    for (auto& font : fonts)
    {
        const std::string fontPath = fonts_path + font + ".ttf";
        const std::string metadataPath = generated + font + ".meta";
        const std::string atlasPath = generated + font + ".png";;
        generator.generate(fontPath.c_str(), atlasPath.c_str(), metadataPath.c_str());
    }
    return 0;
}
