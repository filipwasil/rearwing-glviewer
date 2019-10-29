#pragma once

namespace rwc
{

class FontGenerator
{
public:
/*
* @brief generates font atlas in non-compressed png and text file with texture
 *
 * @param ttfFilePath path to true type font file
 *
 * @param outputPNG path to png file
 *
 * @param outputMETADATA path to metadata file
 */
    int generate(const char* ttfFilePath, const char* outputPNG, const char* outputMETADATA);
};

} // namespace rwc
