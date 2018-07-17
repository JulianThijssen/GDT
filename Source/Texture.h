#pragma once

#include <glad/glad.h>

typedef unsigned int uint;

enum Sampling
{
    NONE,
    NEAREST,
    LINEAR
};

enum Wrapping
{
    CLAMP = GL_CLAMP_TO_EDGE,
    REPEAT = GL_REPEAT,
    BORDER = GL_CLAMP_TO_BORDER
};

enum TextureUnit;

class Texture
{
public:
    Texture(GLenum target);
    void create();
    void bind(TextureUnit textureUnit);
    void release();
    void setSampling(Sampling minFilter, Sampling magFilter, Sampling mipFilter = NONE);
    bool isCreated();
    void destroy();

protected:
    bool created = false;

    GLenum target;
    GLuint handle;
};

class Texture2D : public Texture
{
public:
    Texture2D();
    void setData(uint width, uint height, GLint internalFormat, GLenum format, GLenum type, const void* data);

private:
    uint width, height;
};
