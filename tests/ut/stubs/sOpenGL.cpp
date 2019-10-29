#include <glad/glad.h>

PFNGLGETPROGRAMIVPROC glad_glGetProgramiv = [](
    GLuint /*program*/
    , GLenum /*pname*/
    , GLint *params)
{
    *params = 1;
};

PFNGLGETACTIVEATTRIBPROC glad_glGetActiveAttrib = [] (
    GLuint /*program*/
    , GLuint /*index*/
    , GLsizei /*bufSize*/
    , GLsizei */*length*/
    , GLint */*size*/
    , GLenum */*type*/
    , GLchar */*name*/)
{
    // empty
};

PFNGLGETATTRIBLOCATIONPROC glad_glGetAttribLocation = [] (
    GLuint /*program*/
    , const GLchar */*name*/)
{
    return 0;
};

PFNGLENABLEPROC glad_glEnable = [](
    GLenum /*target*/) {};

PFNGLBLENDFUNCPROC glad_glBlendFunc = [](
    GLenum /*sfactor*/
    , GLenum /*dfactor*/)
{
    // empty
};

PFNGLDRAWARRAYSPROC glad_glDrawArrays = [] (
    GLenum /*mode*/
    , GLint /*first*/
    , GLsizei /*count*/)
{
    // empty
};

PFNGLDISABLEPROC glad_glDisable = [] (GLenum /*cap*/) {};

PFNGLDRAWELEMENTSPROC glad_glDrawElements = [] (
    GLenum /*mode*/
    , GLsizei /*count*/
    , GLenum /*type*/
    , const void */*indices*/) {};

PFNGLGETINTEGERVPROC glad_glGetIntegerv = [] (
    GLenum /*pname*/
    , GLint *data)
{
    *data = 1;
};

PFNGLFRONTFACEPROC glad_glFrontFace = [] (
    GLenum /*mode*/)
{
    // empty
};

PFNGLGETERRORPROC glad_glGetError = [] ()
{
    return GLenum(GL_NO_ERROR);
};

PFNGLGETUNIFORMLOCATIONPROC glad_glGetUniformLocation = [] (
    GLuint /*program*/
    , const GLchar */*name*/)
{
    return -1;
};

PFNGLTEXIMAGE2DPROC glad_glTexImage2D = [](
    GLenum /*target*/
    , GLint /*level*/
    , GLint /*internalformat*/
    , GLsizei /*width*/
    , GLsizei /*height*/
    , GLint /*border*/
    , GLenum /*format*/
    , GLenum /*type*/
    , const void */*pixels*/)
{
    // empty
};

PFNGLPIXELSTOREIPROC glad_glPixelStorei = [] (
    GLenum /*pname*/
    , GLint /*param*/)
{
    // empty
};

PFNGLCOMPRESSEDTEXIMAGE2DPROC glad_glCompressedTexImage2D = [] (
    GLenum /*target*/
    , GLint /*level*/
    , GLenum /*internalformat*/
    , GLsizei /*width*/
    , GLsizei /*height*/, GLint /*border*/, GLsizei /*imageSize*/, const void */*data*/)
{
    // empty
};

PFNGLCOLORMASKPROC glad_glColorMask = [] (
    GLboolean /*red*/
    , GLboolean /*green*/
    , GLboolean /*blue*/
    , GLboolean /*alpha*/)
{
    // empty
};

PFNGLDEPTHMASKPROC glad_glDepthMask = [] (
    GLboolean /*flag*/)
{
    // empty
};

PFNGLBLENDEQUATIONPROC glad_glBlendEquation = [] (
    GLenum /*mode*/)
{
    // empty
};

PFNGLCREATEPROGRAMPROC glad_glCreateProgram = []()
{
    return GLuint(1);
};

PFNGLCREATESHADERPROC glad_glCreateShader = [](
    GLenum /*type*/)
{
    return GLuint(0);
};

PFNGLCOMPILESHADERPROC glad_glCompileShader = [](
    GLenum /*type*/)
{
    // empty
};

PFNGLSHADERBINARYPROC glad_glShaderBinaryOES = [] (
    GLsizei /*count*/
    , const GLuint */*shaders*/
    , GLenum /*binaryformat*/
    , const void */*binary*/
    , GLsizei /*length*/)
{
    // empty
};

PFNGLSHADERSOURCEPROC glad_glShaderSource = [] (
    GLuint /*shader*/
    , GLsizei /*count*/
    , const GLchar *const*/*string*/
    , const GLint */*length*/)
{

};

PFNGLACTIVETEXTUREPROC glad_glActiveTexture = [] (
    GLenum /*texture*/)
{
    // empty
};

PFNGLATTACHSHADERPROC glad_glAttachShader = [] (
    GLuint /*program*/
    , GLuint /*shader*/)
{
    // empty
};

PFNGLGETSHADERIVPROC glad_glGetShaderiv = [](
    GLuint /*shader*/
    , GLenum /*pname*/
    , GLint *params)
{
    *params = 1;
};

PFNGLGETSHADERINFOLOGPROC glad_glGetShaderInfoLog = [] (
    GLuint /*shader*/
    , GLsizei /*bufSize*/
    , GLsizei */*length*/
    , GLchar */*infoLog*/)
{
    // empty
};

PFNGLDELETESHADERPROC glad_glDeleteShader = [] (
    GLuint /*shader*/)
{
    // empty
};

PFNGLLINKPROGRAMPROC glad_glLinkProgram = [] (
    GLuint /*program*/)
{
    // empty
};

PFNGLUSEPROGRAMPROC glad_glUseProgram = [] (
    GLuint /*program*/)
{
    // empty
};

PFNGLVALIDATEPROGRAMPROC glad_glValidateProgram = [] (
    GLuint /*program*/)
{
    // empty
};

PFNGLGETPROGRAMBINARYOESPROC glad_glGetProgramBinaryOES = [] (
    GLuint /*program*/
    , GLsizei /*bufSize*/
    , GLsizei */*length*/
    , GLenum */*binaryFormat*/
    , void*/*binary*/)
{
    // empty
};

PFNGLPROGRAMBINARYOESPROC glad_glProgramBinaryOES = [] (
    GLuint /*program*/
    , GLenum /*binaryFormat*/
    , const void */*binary*/
    , GLint /*length*/)
{
    // empty
};

PFNGLPROGRAMBINARYPROC glad_glProgramBinary = [] (
    GLuint /*program*/
    , GLenum /*binaryFormat*/
    , const void */*binary*/
    , GLsizei /*length*/)
{
    // empty
};

PFNGLGETPROGRAMINFOLOGPROC glad_glGetProgramInfoLog = [] (
    GLuint /*program*/
    , GLsizei /*bufSize*/
    , GLsizei */*length*/
    , GLchar */*infoLog*/)
{
    // empty
};

PFNGLGENTEXTURESPROC glad_glGenTextures = [](GLsizei /*n*/, GLuint *textures)
{
    *textures = 1;
};

PFNGLBINDTEXTUREPROC glad_glBindTexture = [](GLenum /*target*/, GLuint /*texture*/)
{
    // empty
};

PFNGLGENFRAMEBUFFERSPROC glad_glGenFramebuffers = [](GLsizei /*n*/, GLuint *framebuffers)
{
    *framebuffers = 1;
};

PFNGLGENERATEMIPMAPPROC glad_glGenerateMipmap = [](GLenum /*target*/)
{
    // empty
};

PFNGLTEXPARAMETERIPROC glad_glTexParameteri = [](GLenum /*target*/, GLenum /*pname*/, GLint /*param*/)
{
    // empty
};
