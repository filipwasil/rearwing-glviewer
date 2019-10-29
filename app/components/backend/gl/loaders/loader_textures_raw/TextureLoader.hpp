#pragma once

namespace rwc
{

/*!
 * @class TextureLoader
 *
 * @brief Encapsulates creation of OpenGL texture objects
 *
 */
class TextureLoader
{
public:
/*!
 * @brief Initialize create and return OpnGL Texture object
 *
 * @param[in] filePath path to the texture file
 *
 * @return OpenGL texture id (name)
 *
 */
    unsigned int load(const char* filePath);

private:
    unsigned int loadEmpty(
        int width
        , int height
        , unsigned int format
        , int internalFormat);

    unsigned int loadColor(
        int width
        , int height
        , unsigned char red
        , unsigned char green
        , unsigned char blue
        , unsigned int format
        , int internalFormat);

    unsigned int loadChessboard(
        int width
        , int height
        , unsigned char red
        , unsigned char green
        , unsigned char blue
        , unsigned int format
        , int internalFormat);

    unsigned int loadFromFile(
        const char* filePath
        , unsigned int format
        , int internalFormat);
};

} // namespace rwc
