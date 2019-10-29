#include "FontFactory.hpp"

#include <Exception.hpp>

#include <fstream>
#include <string>

namespace rwc
{

Text::Font FontFactory::create(const char* metadataPath)
{
    Text::Font font;
    std::ifstream myfile(metadataPath);
    if (!myfile.is_open()) {
        throw Exception{"Font metadata failed to load", LOCATION};
    }
    std::string line;
    std::string ASCII, xMin, width, yMin, height, yOffset;
    float fXMin, fWidth, fYMin, fHeight, fYOffset;
    int iASCII;

    int control = 0;
    constexpr int maxMetadataLinesSize = 512;
    while (!myfile.eof())
    {
        getline(myfile, line);
        myfile >> iASCII >> fXMin >> fWidth >> fYMin >> fHeight >> fYOffset;
        font.widths[iASCII] = fWidth;
        font.offsets[iASCII] = 1.0f - fHeight - fYOffset;
        if (control++ > maxMetadataLinesSize)
        {
            throw Exception{"Font metadata file corrupted to load", LOCATION};
        }
    }
    return font;
}

}  // namespace rwc
